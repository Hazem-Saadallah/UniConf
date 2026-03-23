#pragma once

#include "BaseManager.hxx"
#include <TomlManager.hxx>
#include <toml++/toml.hpp>

class ITomlManager : public IBaseManager {
private:
  toml::table m_Table;

public:
  ITomlManager() = default;
  ITomlManager(const std::string& file_path);
  ~ITomlManager() = default;
  ITomlManager(ITomlManager &&) noexcept = delete;
  ITomlManager &operator=(ITomlManager &&) noexcept = delete;
  ITomlManager(const ITomlManager &) = delete;
  ITomlManager &operator=(const ITomlManager &) = delete;

  void load(const std::string& file_path) override;
  void save(std::optional<std::string> file_path) override;
  void refresh() override; 

  template<typename T> std::optional<T> get_as(const std::string& path) {
    return  m_Table.at_path(path).value<T>();
  };

  std::optional<std::string> get_string(const std::string& path) override;
  std::optional<std::int64_t> get_int64(const std::string& path) override;
  std::optional<bool> get_bool(const std::string& path) override;
  std::optional<std::double_t> get_float64(const std::string& path) override;
};
