#include "UniConf/Impl/Util/Macro.hxx"
#include <mutex>
#include <fstream>
#include <optional>
#include <shared_mutex>
#include <string>
#include <toml++/toml.hpp>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/TomlManager.hxx>


UniConf::Impl::TomlManager::TomlManager(const std::string& file_path) : BaseManager(file_path) {
  load(file_path);
}

void UniConf::Impl::TomlManager::load_parser() {
  m_Table = toml::parse_file(m_ConfigPath);
}

void UniConf::Impl::TomlManager::save(std::optional<std::string> file_path) {
  std::unique_lock<std::shared_mutex> lock(m_RWMutex);
  std::ofstream(file_path.value_or(m_ConfigPath)) << m_Table;
}

GET_STRING_DEFINITION(UniConf::Impl::TomlManager);
GET_BOOL_DEFINITION(UniConf::Impl::TomlManager);
GET_FLOAT_DEFINITION(UniConf::Impl::TomlManager);
GET_SIGN_INT_DEFINITION(UniConf::Impl::TomlManager);
GET_UINT8_DEFINITION(UniConf::Impl::TomlManager);
GET_UINT16_DEFINITION(UniConf::Impl::TomlManager);
GET_UINT32_DEFINITION(UniConf::Impl::TomlManager);
std::optional<std::uint64_t> UniConf::Impl::TomlManager::get_uint64(const Datatype::PathType& full_path) const {
  if(std::optional<std::string> val = get_as<std::string>(full_path)) return std::stoull(*val);
  return std::nullopt;
}
std::optional<std::uint64_t> UniConf::Impl::TomlManager::get_uint64(const Datatype::PathType& path, const std::string& key) const {
  if(std::optional<std::string> val = get_as<std::string>(path, key)) return std::stoull(*val);
  return std::nullopt;
}

SET_STRING_DEFINITION(UniConf::Impl::TomlManager);
SET_BOOL_DEFINITION(UniConf::Impl::TomlManager);
SET_FLOAT_DEFINITION(UniConf::Impl::TomlManager);
SET_SIGN_INT_DEFINITION(UniConf::Impl::TomlManager);
SET_UINT8_DEFINITION(UniConf::Impl::TomlManager);
SET_UINT16_DEFINITION(UniConf::Impl::TomlManager);
SET_UINT32_DEFINITION(UniConf::Impl::TomlManager);
void UniConf::Impl::TomlManager::set_uint64(const Datatype::PathType& full_path, std::uint64_t value) { set_as<std::string>(full_path, std::to_string(value)); }
void UniConf::Impl::TomlManager::set_uint64(const Datatype::PathType& path, const std::string& key, std::uint64_t value) { set_as<std::string>(path, key, std::to_string(value)); }

SET_OR_CREATE_STRING_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_BOOL_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_FLOAT_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_SIGN_INT_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_UINT8_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_UINT16_DEFINITION(UniConf::Impl::TomlManager);
SET_OR_CREATE_UINT32_DEFINITION(UniConf::Impl::TomlManager);
void UniConf::Impl::TomlManager::set_or_create_uint64(const Datatype::PathType& full_path, std::uint64_t value) { set_or_create_as<std::string>(full_path, std::to_string(value)); }
void UniConf::Impl::TomlManager::set_or_create_uint64(const Datatype::PathType& path, const std::string& key, std::uint64_t value) { set_or_create_as<std::string>(path, key, std::to_string(value)); }

bool UniConf::Impl::TomlManager::path_exists(const std::vector<std::string>& path) const {
  std::unique_lock<std::shared_mutex> lock(m_RWMutex);
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
