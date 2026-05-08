#pragma once

#include <mutex>
#include <span>
#include <string>
#include <vector>
#include <concepts>
#include <shared_mutex>
#include <pugixml.hpp>
#include <UniConf/Impl/datatypes.hxx>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/Util/Macro.hxx>


namespace UniConf {
  namespace Impl {
    template <typename U> concept XmlValueSource = std::same_as<U, pugi::xml_attribute> || std::same_as<U, pugi::xml_text>;

    class XMLManager : public UniConf::Impl::BaseManager {
    private:
      pugi::xml_document m_Document;

    public:
      XMLManager() = default;
      XMLManager(const std::string& file_path);
      ~XMLManager() = default;
      XMLManager(XMLManager&& other) noexcept = delete;
      XMLManager &operator=(XMLManager&& other) noexcept = delete;
      XMLManager(const XMLManager& other) = delete;
      XMLManager &operator=(const XMLManager& other) = delete;
    private:
      std::optional<pugi::xml_node> navigate_parents(std::span<const std::string> path, bool create_missing=false) const;

      template<typename T, XmlValueSource SourceType> std::optional<T> extract_value(SourceType source) const {
        if constexpr (std::is_same_v<T, std::string>) return std::string(source.as_string());
        else if constexpr (std::is_same_v<T, bool>) return source.as_bool();
        else if constexpr (std::is_floating_point_v<T>) {
          if constexpr (sizeof(T) == 8) return static_cast<T>(source.as_double());
          else return static_cast<T>(source.as_float());
        }
        else if constexpr (std::is_integral_v<T>) {
          if constexpr (sizeof(T) == 8) {
            if constexpr (std::is_signed_v<T>) return static_cast<T>(source.as_llong());
            else return static_cast<T>(source.as_ullong());
          } else {
            if constexpr (std::is_signed_v<T>) return static_cast<T>(source.as_int());
            else return static_cast<T>(source.as_uint());
          }
        }
        else return std::nullopt;
      }

      template <typename T> std::optional<T> get_as_impl(const Datatype::PathType& full_path) const {
        Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
        std::string key = full_path.back();

        if(key.empty()) return std::nullopt;
        std::optional<pugi::xml_node> parent = navigate_parents(path, false);
        if(!parent) return std::nullopt;
        pugi::xpath_node target = parent->select_node(key.c_str());
        if(target.attribute()) return extract_value<T, pugi::xml_attribute>(target.attribute());
        else if (target.node()) return extract_value<T, pugi::xml_text>(target.node().text());
        return std::nullopt;
      }

      template<typename T> void set_as_impl(const std::vector<std::string>& full_path, const T& value) {
        if(full_path.empty()) return;

        Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
        std::string key = full_path.back();

        std::optional<pugi::xml_node> node = navigate_parents(path, false);
        if(!node.has_value()) return;
        if(key[0] == '@') {
          std::string attribute_name = key.substr(1);
          pugi::xml_attribute attribute = node.value().attribute(attribute_name.c_str());
          if(attribute) {
            if constexpr (std::is_same_v<T, std::string>) attribute.set_value(value.c_str());
            else attribute.set_value(value);
          } else { /* TODO: Add error handling */ }
        } else {
          pugi::xml_node child = node.value().child(key.c_str());
          if(child) {
            if constexpr (std::is_same_v<T, std::string>) child.text().set(value.c_str());
            else child.text().set(value);
          } else { /* TODO: Add error handling */ }
        }
      }

      template<typename T> void set_or_create_as_impl(const std::vector<std::string>& full_path, const T& value) {
        Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
        std::string key = full_path.back();

        if(key.empty()) return;

        std::optional<pugi::xml_node> node = navigate_parents(path, true);
        if(!node.has_value()) return;
        if(key[0] == '@') {
          std::string attribute_name = key.substr(1);
          pugi::xml_attribute attribute = node.value().attribute(attribute_name.c_str());
          if(!attribute) attribute = node.value().append_attribute(attribute_name.c_str());
          if constexpr (std::is_same_v<T, std::string>) attribute.set_value(value.c_str());
          else attribute.set_value(value);
        } else {
          pugi::xml_node child = node.value().child(key.c_str());
          if(!child) child = node.value().append_child(key.c_str());
          if constexpr (std::is_same_v<T, std::string>) child.text().set(value.c_str());
          else child.text().set(value);
        }
      }

    public:
      void load_parser() override;
      void save(std::optional<std::string> file_path=std::nullopt) override;

      bool path_exists(const std::vector<std::string>& path) const override;
      void create_table(const std::vector<std::string>& path) override;

      GET_AS();
      GET_ALL_DECLARATIONS();

      SET_AS();
      SET_ALL_DECLARATIONS();

      SET_OR_CREATE_AS();
      SET_OR_CREATE_ALL_DECLARATIONS();
    };
  }
}
