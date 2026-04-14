#include <fstream>
#include <optional>
#include <filesystem>
#include <toml++/toml.hpp>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/TomlManager.hxx>


UniConf::Impl::TomlManager::TomlManager(const std::string& file_path) : BaseManager(file_path) {
  load(file_path);
}

void UniConf::Impl::TomlManager::load(const std::string& file_path) {
  if(m_Initalized) return;
  if(!std::filesystem::exists(file_path)) {
    /* TODO: Add the "Get Last Error" feature */
    return;
  }
  m_Table = toml::parse_file(file_path);
  m_Initalized = true;
}

void UniConf::Impl::TomlManager::save(std::optional<std::string> file_path) { std::ofstream(file_path.value_or(m_ConfigPath)) << m_Table; }
void UniConf::Impl::TomlManager::refresh() { load(m_ConfigPath); }

std::optional<std::string> UniConf::Impl::TomlManager::get_string(const std::string& full_path) const { return get_as<std::string>(full_path); }
std::optional<std::string> UniConf::Impl::TomlManager::get_string(const std::vector<std::string>& full_path) const { return get_as<std::string>(full_path); }
std::optional<std::string> UniConf::Impl::TomlManager::get_string(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::string>(path, key); }

std::optional<std::int8_t> UniConf::Impl::TomlManager::get_int8(const std::string& full_path) const { return get_as<std::int8_t>(full_path); }
std::optional<std::int8_t> UniConf::Impl::TomlManager::get_int8(const std::vector<std::string>& full_path) const { return get_as<std::int8_t>(full_path); }
std::optional<std::int8_t> UniConf::Impl::TomlManager::get_int8(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int8_t>(path, key); }
std::optional<std::uint8_t> UniConf::Impl::TomlManager::get_uint8(const std::string& full_path) const { return get_as<std::uint8_t>(full_path); }
std::optional<std::uint8_t> UniConf::Impl::TomlManager::get_uint8(const std::vector<std::string>& full_path) const { return get_as<std::uint8_t>(full_path); }
std::optional<std::uint8_t> UniConf::Impl::TomlManager::get_uint8(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint8_t>(path, key); }

std::optional<std::int16_t> UniConf::Impl::TomlManager::get_int16(const std::string& full_path) const { return get_as<std::int16_t>(full_path); }
std::optional<std::int16_t> UniConf::Impl::TomlManager::get_int16(const std::vector<std::string>& full_path) const { return get_as<std::int16_t>(full_path); }
std::optional<std::int16_t> UniConf::Impl::TomlManager::get_int16(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int16_t>(path, key); }
std::optional<std::uint16_t> UniConf::Impl::TomlManager::get_uint16(const std::string& full_path) const { return get_as<std::uint16_t>(full_path); }
std::optional<std::uint16_t> UniConf::Impl::TomlManager::get_uint16(const std::vector<std::string>& full_path) const { return get_as<std::uint16_t>(full_path); }
std::optional<std::uint16_t> UniConf::Impl::TomlManager::get_uint16(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint16_t>(path, key); }

std::optional<std::int32_t> UniConf::Impl::TomlManager::get_int32(const std::string& full_path) const { return get_as<std::int32_t>(full_path); }
std::optional<std::int32_t> UniConf::Impl::TomlManager::get_int32(const std::vector<std::string>& full_path) const { return get_as<std::int32_t>(full_path); }
std::optional<std::int32_t> UniConf::Impl::TomlManager::get_int32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int32_t>(path, key); }
std::optional<std::uint32_t> UniConf::Impl::TomlManager::get_uint32(const std::string& full_path) const { return get_as<std::uint32_t>(full_path); }
std::optional<std::uint32_t> UniConf::Impl::TomlManager::get_uint32(const std::vector<std::string>& full_path) const { return get_as<std::uint32_t>(full_path); }
std::optional<std::uint32_t> UniConf::Impl::TomlManager::get_uint32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint32_t>(path, key); }

std::optional<std::int64_t> UniConf::Impl::TomlManager::get_int64(const std::string& full_path) const { return get_as<std::int64_t>(full_path); }
std::optional<std::int64_t> UniConf::Impl::TomlManager::get_int64(const std::vector<std::string>& full_path) const { return get_as<std::int64_t>(full_path); }
std::optional<std::int64_t> UniConf::Impl::TomlManager::get_int64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int64_t>(path, key); }
std::optional<std::uint64_t> UniConf::Impl::TomlManager::get_uint64(const std::string& full_path) const  { return get_as<std::uint64_t>(full_path); }
std::optional<std::uint64_t> UniConf::Impl::TomlManager::get_uint64(const std::vector<std::string>& full_path) const  { return get_as<std::uint64_t>(full_path); }
std::optional<std::uint64_t> UniConf::Impl::TomlManager::get_uint64(const std::vector<std::string>& path, const std::string& key) const  { return get_as<std::uint64_t>(path, key); }

std::optional<std::float_t> UniConf::Impl::TomlManager::get_float32(const std::string& full_path) const { return get_as<std::float_t>(full_path); }
std::optional<std::float_t> UniConf::Impl::TomlManager::get_float32(const std::vector<std::string>& full_path) const { return get_as<std::float_t>(full_path); }
std::optional<std::float_t> UniConf::Impl::TomlManager::get_float32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::float_t>(path, key); }
std::optional<std::double_t> UniConf::Impl::TomlManager::get_float64(const std::string& full_path) const { return get_as<std::double_t>(full_path); }
std::optional<std::double_t> UniConf::Impl::TomlManager::get_float64(const std::vector<std::string>& full_path) const { return get_as<std::double_t>(full_path); }
std::optional<std::double_t> UniConf::Impl::TomlManager::get_float64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::double_t>(path, key); }

std::optional<bool> UniConf::Impl::TomlManager::get_bool(const std::string& full_path) const { return get_as<bool>(full_path); }
std::optional<bool> UniConf::Impl::TomlManager::get_bool(const std::vector<std::string>& full_path) const { return get_as<bool>(full_path); }
std::optional<bool> UniConf::Impl::TomlManager::get_bool(const std::vector<std::string>& path, const std::string& key) const { return get_as<bool>(path, key); }

bool UniConf::Impl::TomlManager::path_exists(const std::vector<std::string>& path) const {
  if(path.empty()) return false;
  const toml::table *current = &m_Table;
  for(std::size_t i{0}; i < path.size(); ++i) {
    const std::string& key = path[i];
    const toml::node* next_node = current->get(key);
    if(!next_node) return false;
    if(i == path.size()-1) return true;
    if(!next_node->is_table()) return false;;
    current = next_node->as_table();
  }
  return true;
}

void UniConf::Impl::TomlManager::create_table(const std::vector<std::string>& path) {
  toml::table *current = &m_Table;
  for(std::size_t i{0}; i < path.size(); ++i) {
    if(!current->contains(path.at(i)) || !(*current).at(path.at(i)).is_table()) current->insert_or_assign(path.at(i), toml::table{});
    current = (*current).at(path.at(i)).as_table();
  }
}

void UniConf::Impl::TomlManager::set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_as<std::string>(path, key, value); }
void UniConf::Impl::TomlManager::set_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value)  { set_as<std::int8_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value)  { set_as<std::uint8_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value)  { set_as<std::int16_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value)  { set_as<std::uint16_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value)  { set_as<std::int32_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value)  { set_as<std::uint32_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_as<std::int64_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value)  { set_as<std::string>(path, key, std::to_string(value)); }
void UniConf::Impl::TomlManager::set_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) { set_as<std::float_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_as<std::double_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_as<bool>(path, key, value); }

void UniConf::Impl::TomlManager::set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_or_create_as<std::string>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value)  { set_or_create_as<std::int8_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value)  { set_or_create_as<std::uint8_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value)  { set_or_create_as<std::int16_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value)  { set_or_create_as<std::uint16_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value)  { set_or_create_as<std::int32_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value)  { set_or_create_as<std::uint32_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_or_create_as<std::int64_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value)  { set_or_create_as<std::string>(path, key, std::to_string(value)); }
void UniConf::Impl::TomlManager::set_or_create_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) { set_or_create_as<std::float_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_or_create_as<std::double_t>(path, key, value); }
void UniConf::Impl::TomlManager::set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_or_create_as<bool>(path, key, value); }
