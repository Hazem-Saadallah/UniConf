#pragma once

#include <mutex>
#include <string>
#include <cstddef>
#include <utility>
#include <vector>
#include <shared_mutex>
#include <toml++/toml.hpp>
#include <UniConf/Impl/datatypes.hxx>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/TomlManager.hxx>
#include <UniConf/Impl/Util/Macro.hxx>

namespace UniConf {
  namespace Impl {
  class TomlManager : public UniConf::Impl::BaseManager {
  private:
    toml::table m_Table;

  private:
    template<typename T> inline std::optional<T> get_as_impl(const std::vector<std::string>& full_path) const {
      if(full_path.empty()) return std::nullopt;
      const toml::table *current = &m_Table;
      for(std::size_t i{0}; i < full_path.size()-1; ++i) {
        const std::string& path_part = full_path[i];
        const toml::node* next_node = current->get(path_part);
        if(!next_node || !next_node->is_table()) return std::nullopt;
        current = next_node->as_table();
      }
      if(!current->get(full_path.back())) return std::nullopt;
      return current->get(full_path.back())->value<T>();
    }

    template <typename T> inline void set_as_impl(const std::vector<std::string>& full_path, T value) {
      toml::table *current = &m_Table;
      for(std::size_t i{0}; i < full_path.size()-1; ++i) {
        const std::string& path_part = full_path[i];
        toml::node* next_node = current->get(path_part);
        if(!next_node || !next_node->is_table()) return; /* TODO: Add error handling */
        current = next_node->as_table();
      }
      current->insert_or_assign(full_path.back(), std::forward<T>(value));
    }

    template <typename T> inline void set_or_create_as_impl(const std::vector<std::string>& full_path, T value) {
      Datatype::PathType path = Datatype::PathType(full_path.begin(), full_path.end()-1);
      std::string key = full_path.back();
      create_table(path);
      toml::table *current = &m_Table;
      for(std::size_t i{0}; i < path.size(); ++i)  current = (*current).at(path.at(i)).as_table();
      current->insert_or_assign(key, std::forward<T>(value));
    }


  public:
    TomlManager() = default;
    TomlManager(const std::string& file_path);
    ~TomlManager() = default;
    TomlManager(TomlManager&& other) noexcept = delete;
    TomlManager &operator=(TomlManager&& other) noexcept = delete;
    TomlManager(const TomlManager& other) = delete;
    TomlManager &operator=(const TomlManager& other) = delete;

    void load_parser() override;
    void save(std::optional<std::string> file_path=std::nullopt) override;

    GET_AS();
    GET_ALL_DECLARATIONS();

    SET_AS();
    SET_ALL_DECLARATIONS();

    SET_OR_CREATE_AS();
    SET_OR_CREATE_ALL_DECLARATIONS();

    bool path_exists(const Datatype::PathType& path) const override;
    void create_table(const Datatype::PathType& path) override;
  };
  }
}
