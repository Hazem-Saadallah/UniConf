#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <cstdint>
#include <optional>

class IBaseManager {
protected:
  std::string m_ConfigPath{""};
  bool m_Initalized{false};

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
  virtual void save(std::optional<std::string> file_path=std::nullopt) = 0;
  virtual void refresh() = 0;
  
  virtual std::optional<std::string> get_string(const std::string& full_path) const = 0;
  virtual std::optional<std::string> get_string(const std::vector<std::string>& full_path) const = 0;
  virtual std::optional<std::string> get_string(const std::vector<std::string>& path, const std::string& key) const = 0;

  virtual std::optional<std::int64_t> get_int64(const std::string& full_path) const = 0;
  virtual std::optional<std::int64_t> get_int64(const std::vector<std::string>& full_path) const = 0;
  virtual std::optional<std::int64_t> get_int64(const std::vector<std::string>& path, const std::string& key) const = 0;

  virtual std::optional<std::double_t> get_float64(const std::string& full_path) const = 0;
  virtual std::optional<std::double_t> get_float64(const std::vector<std::string>& full_path) const = 0;
  virtual std::optional<std::double_t> get_float64(const std::vector<std::string>& path, const std::string& key) const = 0;

  virtual std::optional<bool> get_bool(const std::string& full_path) const = 0;
  virtual std::optional<bool> get_bool(const std::vector<std::string>& full_path) const = 0;
  virtual std::optional<bool> get_bool(const std::vector<std::string>& path, const std::string& key) const = 0;

  virtual bool path_exists(const std::vector<std::string>& path) const = 0;
  virtual void create_table(const std::vector<std::string>& path) = 0;

  virtual void set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) = 0;
  virtual void set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) = 0;
  virtual void set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) = 0;
  virtual void set_bool(const std::vector<std::string>& path, const std::string& key, bool value) = 0;

  virtual void set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) = 0;
  virtual void set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) = 0;
  virtual void set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) = 0;
  virtual void set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) = 0;
};
