#include <cmath>
#include <fstream>
#include <optional>
#include <filesystem>
#include <toml++/toml.hpp>
#include <BaseManager.hxx>
#include <TomlManager.hxx>


ITomlManager::ITomlManager(const std::string& file_path) : IBaseManager(file_path) {
  load(file_path);
}

void ITomlManager::load(const std::string& file_path) {
  if(m_Initalized) return;
  if(!std::filesystem::exists(file_path)) {
    /* TODO: Add the "Get Last Error" feature */
    return;
  }
  m_Table = toml::parse_file(file_path);
  m_Initalized = true;
}

void ITomlManager::save(std::optional<std::string> file_path) { std::ofstream(file_path.value_or(m_ConfigPath)) << m_Table; }
void ITomlManager::refresh() { load(m_ConfigPath); }

std::optional<std::string> ITomlManager::get_string(const std::string& full_path) const { return get_as<std::string>(full_path); }
std::optional<std::string> ITomlManager::get_string(const std::vector<std::string>& full_path) const { return get_as<std::string>(full_path); }
std::optional<std::string> ITomlManager::get_string(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::string>(path, key); }

std::optional<std::int64_t> ITomlManager::get_int64(const std::string& full_path) const { return get_as<std::int64_t>(full_path); }
std::optional<std::int64_t> ITomlManager::get_int64(const std::vector<std::string>& full_path) const { return get_as<std::int64_t>(full_path); }
std::optional<std::int64_t> ITomlManager::get_int64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int64_t>(path, key); }

std::optional<std::double_t> ITomlManager::get_float64(const std::string& full_path) const { return get_as<std::double_t>(full_path); }
std::optional<std::double_t> ITomlManager::get_float64(const std::vector<std::string>& full_path) const { return get_as<std::double_t>(full_path); }
std::optional<std::double_t> ITomlManager::get_float64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::double_t>(path, key); }

std::optional<bool> ITomlManager::get_bool(const std::string& full_path) const { return get_as<bool>(full_path); }
std::optional<bool> ITomlManager::get_bool(const std::vector<std::string>& full_path) const { return get_as<bool>(full_path); }
std::optional<bool> ITomlManager::get_bool(const std::vector<std::string>& path, const std::string& key) const { return get_as<bool>(path, key); }

bool ITomlManager::path_exists(const std::vector<std::string>& path) const {
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

void ITomlManager::create_table(const std::vector<std::string>& path) {
  toml::table *current = &m_Table;
  for(std::size_t i{0}; i < path.size(); ++i) {
    if(!current->contains(path.at(i)) || !(*current).at(path.at(i)).is_table()) current->insert_or_assign(path.at(i), toml::table{});
    current = (*current).at(path.at(i)).as_table();
  }
}

void ITomlManager::set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_as<std::string>(path, key, value); }
void ITomlManager::set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_as<std::int64_t>(path, key, value); }
void ITomlManager::set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_as<std::double_t>(path, key, value); }
void ITomlManager::set_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_as<bool>(path, key, value); }

void ITomlManager::set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_or_create_as<std::string>(path, key, value); }
void ITomlManager::set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_or_create_as<std::int64_t>(path, key, value); }
void ITomlManager::set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_or_create_as<std::double_t>(path, key, value); }
void ITomlManager::set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_or_create_as<bool>(path, key, value); }
