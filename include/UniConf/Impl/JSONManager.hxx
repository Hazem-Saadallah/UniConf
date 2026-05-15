#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <optional>
#include <type_traits>
#include <nlohmann/json.hpp>
#include <UniConf/Impl/datatypes.hxx>
#include <UniConf/Impl/Util/Macro.hxx>
#include <UniConf/Impl/BaseManager.hxx>

namespace UniConf {
namespace Impl {
class JSONManager : public UniConf::Impl::BaseManager {
private:
  nlohmann::json m_JSON;

public:
  JSONManager() = default;
  JSONManager(const std::string& file_path);
  ~JSONManager() = default;
  JSONManager(JSONManager&& other) noexcept = delete;
  JSONManager &operator=(JSONManager&& other) noexcept = delete;
  JSONManager(const JSONManager& other) = delete;
  JSONManager &operator=(const JSONManager& other) = delete;

private:
  nlohmann::json::json_pointer create_pointer(std::span<const std::string> path) const;

  // Helper to validate types at compile time and runtime
  template <typename ExpectedType> constexpr bool is_json_type_match(const nlohmann::json& element) const {
    if constexpr (std::is_same_v<ExpectedType, std::string>) return element.is_string();
    else if constexpr (std::is_same_v<ExpectedType, bool>) return element.is_boolean();
    else if constexpr (std::is_floating_point_v<ExpectedType>) return element.is_number_float() || element.is_number_integer();
    else if constexpr (std::is_integral_v<ExpectedType>) return element.is_number_integer();
    else { return false; }
  }

  template <typename T> std::optional<T> get_as_impl(const Datatype::PathType& full_path) const {
    nlohmann::json::json_pointer ptr = create_pointer(full_path);
    if(!m_JSON.contains(ptr)) return std::nullopt;
    const nlohmann::json& element = m_JSON[ptr];
    if(is_json_type_match<T>(element)) return element.get<T>();
    return std::nullopt;
  }

  template<typename T> void set_as_impl(const std::vector<std::string>& full_path, const T& value) {
    nlohmann::json::json_pointer ptr = create_pointer(full_path);
    if(!m_JSON.contains(ptr)) {
      /* TODO: Add error handling */
      return;
    }
    m_JSON[ptr] = value;
  }

  template<typename T> void set_or_create_as_impl(const Datatype::PathType& full_path, const T& value) {
    if (full_path.empty()) return;
    nlohmann::json* current = &m_JSON;
    for(std::size_t i{0}; i < full_path.size()-1; ++i) {
      const std::string& key = full_path[i];
      if(!current->is_object()) return;
      nlohmann::json::iterator itr = current->find(key);
      if(itr == current->end()) {
        (*current)[key] = nlohmann::json::object();
        itr = current->find(key);
      } else if(itr->is_object()) {
        /* TODO: Add error handling */
        return;
      }
      current = std::to_address(itr);
    }
    const std::string& leaf_key = full_path.back();
    if(!current->is_object()) {
      /* TODO: Add error handling */
      return;
    }
    (*current)[leaf_key] = value;
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
} /* Impl */
} /* UniConf */
