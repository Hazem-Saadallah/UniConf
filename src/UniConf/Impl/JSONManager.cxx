#include <fstream>
#include <iomanip>
#include <ostream>
#include <nlohmann/json.hpp>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/JSONManager.hxx>

UniConf::Impl::JSONManager::JSONManager(const std::string& file_path) : UniConf::Impl::BaseManager(file_path) {
  load(file_path);
}

nlohmann::json::json_pointer UniConf::Impl::JSONManager::create_pointer(std::span<const std::string> path) const {
  nlohmann::json::json_pointer ptr = nlohmann::json::json_pointer();
  for(std::size_t i{0}; i < path.size(); ++i) ptr /= path[i];
  return ptr;
}

void UniConf::Impl::JSONManager::load_parser() {
  std::ifstream file_stream(m_ConfigPath);
  /* TODO: Add Error Handling */
  m_JSON = nlohmann::json::parse(file_stream);
}

void UniConf::Impl::JSONManager::save(std::optional<std::string> file_path) {
  std::ofstream output_stream(file_path.value_or(m_ConfigPath));
  /* TODO: Add Error Handling */
  output_stream <<std::setw(2) <<m_JSON <<std::endl;
}

bool UniConf::Impl::JSONManager::path_exists(const std::vector<std::string>& path) const {
  nlohmann::json::json_pointer ptr = create_pointer(path);
  return m_JSON.contains(ptr);
}

void UniConf::Impl::JSONManager::create_table(const std::vector<std::string>& path) {
  nlohmann::json::json_pointer ptr = create_pointer(path);
  m_JSON[ptr] = nlohmann::json::object();
}

GET_ALL_DEFINITION(UniConf::Impl::JSONManager);
SET_ALL_DEFINITION(UniConf::Impl::JSONManager);
SET_OR_CREATE_ALL_DEFINITION(UniConf::Impl::JSONManager);
