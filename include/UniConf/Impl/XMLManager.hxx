#pragma once

#include "UniConf/Impl/datatypes.hxx"
#include <mutex>
#include <shared_mutex>
#include <span>
#include <string>
#include <vector>
#include <concepts>
#include <pugixml.hpp>
#include <UniConf/Impl/BaseManager.hxx>


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

      template <typename T> std::optional<T> get_as(const std::vector<std::string>& full_path) const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        if(full_path.empty()) return std::nullopt;
        return get_as<T>(std::vector<std::string>(full_path.begin(), full_path.end()-1), full_path.back());
      }

      template <typename T> std::optional<T> get_as(const std::vector<std::string>& path, const std::string& key) const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        if(key.empty()) return std::nullopt;
        std::optional<pugi::xml_node> parent = navigate_parents(path, false);
        if(!parent) return std::nullopt;
        pugi::xpath_node target = parent->select_node(key.c_str());
        if(target.attribute()) return extract_value<T, pugi::xml_attribute>(target.attribute());
        else if (target.node()) return extract_value<T, pugi::xml_text>(target.node().text());
        return std::nullopt;
      }

      std::optional<std::string> get_string(const std::vector<std::string>& full_path) const override;
      std::optional<std::string> get_string(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<std::int8_t> get_int8(const std::vector<std::string>& full_path) const override;
      std::optional<std::int8_t> get_int8(const std::vector<std::string>& path, const std::string& key) const override;
      std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& full_path) const override;
      std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<std::int16_t> get_int16(const std::vector<std::string>& full_path) const override;
      std::optional<std::int16_t> get_int16(const std::vector<std::string>& path, const std::string& key) const override;
      std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& full_path) const override;
      std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<std::int32_t> get_int32(const std::vector<std::string>& full_path) const override;
      std::optional<std::int32_t> get_int32(const std::vector<std::string>& path, const std::string& key) const override;
      std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& full_path) const override;
      std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<std::int64_t> get_int64(const std::vector<std::string>& full_path) const override;
      std::optional<std::int64_t> get_int64(const std::vector<std::string>& path, const std::string& key) const override;
      std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& full_path) const override;
      std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<std::float_t> get_float32(const std::vector<std::string>& full_path) const override;
      std::optional<std::float_t> get_float32(const std::vector<std::string>& path, const std::string& key) const override;
      std::optional<std::double_t> get_float64(const std::vector<std::string>& full_path) const override;
      std::optional<std::double_t> get_float64(const std::vector<std::string>& path, const std::string& key) const override;

      std::optional<bool> get_bool(const std::vector<std::string>& full_path) const override;
      std::optional<bool> get_bool(const std::vector<std::string>& path, const std::string& key) const override;

      bool path_exists(const std::vector<std::string>& path) const override;
      void create_table(const std::vector<std::string>& path) override;

      template<typename T> void set_as(const std::vector<std::string>& full_path, const T& value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        set_as_impl(full_path, value);
      }

      template<typename T> void set_as(const std::vector<std::string>& path, const std::string& key, const T& value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        Datatype::PathType full_path = path;
        full_path.push_back(key);
        set_as_impl(full_path, value);
      }

      void set_string(const std::vector<std::string>& full_path, const std::string& value) override;
      void set_int8(const std::vector<std::string>& full_path, std::int8_t value) override;
      void set_uint8(const std::vector<std::string>& full_path, std::uint8_t value) override;
      void set_int16(const std::vector<std::string>& full_path, std::int16_t value) override;
      void set_uint16(const std::vector<std::string>& full_path, std::uint16_t value) override;
      void set_int32(const std::vector<std::string>& full_path, std::int32_t value) override;
      void set_uint32(const std::vector<std::string>& full_path, std::uint32_t value) override;
      void set_int64(const std::vector<std::string>& full_path, std::int64_t value) override;
      void set_uint64(const std::vector<std::string>& full_path, std::uint64_t value) override;
      void set_float32(const std::vector<std::string>& full_path, std::float_t value) override;
      void set_float64(const std::vector<std::string>& full_path, std::double_t value) override;
      void set_bool(const std::vector<std::string>& full_path, bool value) override;

      void set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) override;
      void set_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) override;
      void set_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) override;
      void set_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) override;
      void set_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) override;
      void set_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) override;
      void set_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) override;
      void set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) override;
      void set_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) override;
      void set_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) override;
      void set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) override;
      void set_bool(const std::vector<std::string>& path, const std::string& key, bool value) override;


      template<typename T> void set_or_create_as(const std::vector<std::string>& full_path, const T& value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        set_or_create_as_impl(full_path, value);
      }

      template<typename T> void set_or_create_as(const std::vector<std::string>& path, const std::string& key, const T& value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        Datatype::PathType full_path = path;
        full_path.push_back(key);
        set_or_create_as_impl(full_path, value);
      }

      void set_or_create_string(const std::vector<std::string>& full_path, const std::string& value) override;
      void set_or_create_int8(const std::vector<std::string>& full_path, std::int8_t value) override;
      void set_or_create_uint8(const std::vector<std::string>& full_path, std::uint8_t value) override;
      void set_or_create_int16(const std::vector<std::string>& full_path, std::int16_t value) override;
      void set_or_create_uint16(const std::vector<std::string>& full_path, std::uint16_t value) override;
      void set_or_create_int32(const std::vector<std::string>& full_path, std::int32_t value) override;
      void set_or_create_uint32(const std::vector<std::string>& full_path, std::uint32_t value) override;
      void set_or_create_int64(const std::vector<std::string>& full_path, std::int64_t value) override;
      void set_or_create_uint64(const std::vector<std::string>& full_path, std::uint64_t value) override;
      void set_or_create_float32(const std::vector<std::string>& full_path, std::float_t value) override;
      void set_or_create_float64(const std::vector<std::string>& full_path, std::double_t value) override;
      void set_or_create_bool(const std::vector<std::string>& full_path, bool value) override;

      void set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) override;
      void set_or_create_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) override;
      void set_or_create_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) override;
      void set_or_create_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) override;
      void set_or_create_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) override;
      void set_or_create_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) override;
      void set_or_create_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) override;
      void set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) override;
      void set_or_create_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) override;
      void set_or_create_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) override;
      void set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) override;
      void set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) override;
    };
  }
}
