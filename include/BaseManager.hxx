#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <cstdint>
#include <optional>

namespace Impl {
  class BaseManager {
  protected:
    std::string m_ConfigPath{""};
    bool m_Initalized{false};

  public:
    BaseManager() = default;
    BaseManager(const std::string& file_path);
    virtual ~BaseManager() = default;
    BaseManager(BaseManager &&) noexcept = delete;
    BaseManager &operator=(BaseManager &&) noexcept = delete;
    BaseManager(const BaseManager &) = delete;
    BaseManager &operator=(const BaseManager &) = delete;

  public:
    bool is_initalized();
    std::string get_config_path();

    virtual void load(const std::string& file_path) = 0;
    virtual void save(std::optional<std::string> file_path=std::nullopt) = 0;
    virtual void refresh() = 0;
    
    virtual std::optional<std::string> get_string(const std::string& full_path) const = 0;
    virtual std::optional<std::string> get_string(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::string> get_string(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<std::int8_t> get_int8(const std::string& full_path) const = 0;
    virtual std::optional<std::int8_t> get_int8(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::int8_t> get_int8(const std::vector<std::string>& path, const std::string& key) const = 0;
    virtual std::optional<std::uint8_t> get_uint8(const std::string& full_path) const = 0;
    virtual std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::uint8_t> get_uint8(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<std::int16_t> get_int16(const std::string& full_path) const = 0;
    virtual std::optional<std::int16_t> get_int16(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::int16_t> get_int16(const std::vector<std::string>& path, const std::string& key) const = 0;
    virtual std::optional<std::uint16_t> get_uint16(const std::string& full_path) const = 0;
    virtual std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::uint16_t> get_uint16(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<std::int32_t> get_int32(const std::string& full_path) const = 0;
    virtual std::optional<std::int32_t> get_int32(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::int32_t> get_int32(const std::vector<std::string>& path, const std::string& key) const = 0;
    virtual std::optional<std::uint32_t> get_uint32(const std::string& full_path) const = 0;
    virtual std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::uint32_t> get_uint32(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<std::int64_t> get_int64(const std::string& full_path) const = 0;
    virtual std::optional<std::int64_t> get_int64(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::int64_t> get_int64(const std::vector<std::string>& path, const std::string& key) const = 0;
    virtual std::optional<std::uint64_t> get_uint64(const std::string& full_path) const = 0;
    virtual std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::uint64_t> get_uint64(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<std::float_t> get_float32(const std::string& full_path) const = 0;
    virtual std::optional<std::float_t> get_float32(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::float_t> get_float32(const std::vector<std::string>& path, const std::string& key) const = 0;
    virtual std::optional<std::double_t> get_float64(const std::string& full_path) const = 0;
    virtual std::optional<std::double_t> get_float64(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<std::double_t> get_float64(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual std::optional<bool> get_bool(const std::string& full_path) const = 0;
    virtual std::optional<bool> get_bool(const std::vector<std::string>& full_path) const = 0;
    virtual std::optional<bool> get_bool(const std::vector<std::string>& path, const std::string& key) const = 0;

    virtual bool path_exists(const std::vector<std::string>& path) const = 0;
    virtual void create_table(const std::vector<std::string>& path) = 0;

    virtual void set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) = 0;
    virtual void set_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) = 0;
    virtual void set_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) = 0;
    virtual void set_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) = 0;
    virtual void set_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) = 0;
    virtual void set_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) = 0;
    virtual void set_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) = 0;
    virtual void set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) = 0;
    virtual void set_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) = 0;
    virtual void set_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) = 0;
    virtual void set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) = 0;
    virtual void set_bool(const std::vector<std::string>& path, const std::string& key, bool value) = 0;

    virtual void set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) = 0;
    virtual void set_or_create_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) = 0;
    virtual void set_or_create_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) = 0;
    virtual void set_or_create_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) = 0;
    virtual void set_or_create_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) = 0;
    virtual void set_or_create_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) = 0;
    virtual void set_or_create_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) = 0;
    virtual void set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) = 0;
    virtual void set_or_create_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) = 0;
    virtual void set_or_create_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) = 0;
    virtual void set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) = 0;
    virtual void set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) = 0;
  };
}
