#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>
#include <toml++/toml.hpp>
#include <BaseManager.hxx>
#include <TomlManager.hxx>

namespace UniConf {
  namespace Impl {
  class TomlManager : public Impl::BaseManager {
  private:
    toml::table m_Table;

  public:
    TomlManager() = default;
    TomlManager(const std::string& file_path);
    ~TomlManager() = default;
    TomlManager(TomlManager &&) noexcept = delete;
    TomlManager &operator=(TomlManager &&) noexcept = delete;
    TomlManager(const TomlManager &) = delete;
    TomlManager &operator=(const TomlManager &) = delete;

    void load(const std::string& file_path) override;
    void save(std::optional<std::string> file_path=std::nullopt) override;
    void refresh() override; 

    template<typename T> inline std::optional<T> get_as(const std::string& full_path) const {
      return m_Table.at_path(full_path).value<T>();
    };

    template<typename T> inline std::optional<T> get_as(const std::vector<std::string>& full_path) const {
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
    };

    template<typename T> inline std::optional<T> get_as(const std::vector<std::string>& path, const std::string& key) const {
      std::vector<std::string> vec = path;
      vec.push_back(key);
      return get_as<T>(vec);
    };

    std::optional<std::string> get_string(const std::string& full_path) const override;
    std::optional<std::string> get_string(const std::vector<std::string>& full_path) const override;
    std::optional<std::string> get_string(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::int8_t> get_int8(const std::string& full_path) const override;
    std::optional<std::int8_t> get_int8(const std::vector<std::string>& full_path) const override;
    std::optional<std::int8_t> get_int8(const std::vector<std::string>& path, const std::string& key) const override;
    std::optional<std::uint8_t> get_uint8(const std::string& full_path) const override;
    std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& full_path) const override;
    std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::int16_t> get_int16(const std::string& full_path) const override;
    std::optional<std::int16_t> get_int16(const std::vector<std::string>& full_path) const override;
    std::optional<std::int16_t> get_int16(const std::vector<std::string>& path, const std::string& key) const override;
    std::optional<std::uint16_t> get_uint16(const std::string& full_path) const override;
    std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& full_path) const override;
    std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::int32_t> get_int32(const std::string& full_path) const override;
    std::optional<std::int32_t> get_int32(const std::vector<std::string>& full_path) const override;
    std::optional<std::int32_t> get_int32(const std::vector<std::string>& path, const std::string& key) const override;
    std::optional<std::uint32_t> get_uint32(const std::string& full_path) const override;
    std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& full_path) const override;
    std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::int64_t> get_int64(const std::string& full_path) const override;
    std::optional<std::int64_t> get_int64(const std::vector<std::string>& full_path) const override;
    std::optional<std::int64_t> get_int64(const std::vector<std::string>& path, const std::string& key) const override;
    std::optional<std::uint64_t> get_uint64(const std::string& full_path) const override;
    std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& full_path) const override;
    std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::float_t> get_float32(const std::string& full_path) const override;
    std::optional<std::float_t> get_float32(const std::vector<std::string>& full_path) const override;
    std::optional<std::float_t> get_float32(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<std::double_t> get_float64(const std::string& full_path) const override;
    std::optional<std::double_t> get_float64(const std::vector<std::string>& full_path) const override;
    std::optional<std::double_t> get_float64(const std::vector<std::string>& path, const std::string& key) const override;

    std::optional<bool> get_bool(const std::string& full_path) const override;
    std::optional<bool> get_bool(const std::vector<std::string>& full_path) const override;
    std::optional<bool> get_bool(const std::vector<std::string>& path, const std::string& key) const override;

    template <typename T> inline void set_as(const std::vector<std::string>& path, const std::string& key, T value) {
      toml::table *current = &m_Table;
      for(std::size_t i{0}; i < path.size(); ++i) {
        const std::string& path_part = path[i];
        toml::node* next_node = current->get(path_part);
        if(!next_node || !next_node->is_table()) return;
        current = next_node->as_table();
      }
      current->insert_or_assign(key, std::forward<T>(value));
    }

    template <typename T> inline void set_or_create_as(const std::vector<std::string>& path, const std::string& key, T value) {
      create_table(path);
      toml::table *current = &m_Table;
      for(std::size_t i{0}; i < path.size(); ++i)  current = (*current).at(path.at(i)).as_table();
      current->insert_or_assign(key, std::forward<T>(value));
    }

    bool path_exists(const std::vector<std::string>& path) const override;
    void create_table(const std::vector<std::string>& path) override;

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
