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
    return;
  }
  m_Table = toml::parse_file(file_path);
  m_Initalized.store(true);
}

void ITomlManager::save(std::optional<std::string> file_path) {
  if(!std::filesystem::exists(file_path.value_or(""))) file_path=std::nullopt;
  std::ofstream(file_path.value_or(m_ConfigPath)) << m_Table;
}

void ITomlManager::refresh() {
  load(m_ConfigPath);
}

std::optional<std::string> ITomlManager::get_string(const std::string& path) {
  return  m_Table.at_path(path).value<std::string>();
}

std::optional<std::int64_t> ITomlManager::get_int64(const std::string& path) {
  return  m_Table.at_path(path).value<std::int64_t>();
}

std::optional<bool> ITomlManager::get_bool(const std::string& path) {
  return  m_Table.at_path(path).value<bool>();
}

std::optional<std::double_t> ITomlManager::get_float64(const std::string& path) {
  return  m_Table.at_path(path).value<std::double_t>();
}
