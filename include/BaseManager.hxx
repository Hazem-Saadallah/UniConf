#pragma once

#include <atomic>
#include <cmath>
#include <string>
#include <cstdint>
#include <optional>

class IBaseManager {
protected:
  std::string m_ConfigPath{""};
  std::atomic<bool> m_Initalized{false};

public:
  IBaseManager() = default;
  IBaseManager(const std::string& file_path);
  virtual ~IBaseManager() = default;
  IBaseManager(IBaseManager &&) noexcept = delete;
  IBaseManager &operator=(IBaseManager &&) noexcept = delete;
  IBaseManager(const IBaseManager &) = delete;
  IBaseManager &operator=(const IBaseManager &) = delete;

public:
  bool is_initalized();
  std::string get_config_path();

  virtual void load(const std::string& file_path) = 0;
  virtual void save(std::optional<std::string> file_path) = 0;
  virtual void refresh() = 0;
  
  virtual std::optional<std::string> get_string(const std::string& key) = 0;
  virtual std::optional<std::int64_t> get_int64(const std::string& key) = 0;
  virtual std::optional<bool> get_bool(const std::string& key) = 0;
  virtual std::optional<std::double_t> get_float64(const std::string& key) = 0;
};
