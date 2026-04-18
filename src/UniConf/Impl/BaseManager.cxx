#include <mutex>
#include <filesystem>
#include <UniConf/Impl/BaseManager.hxx>

UniConf::Impl::BaseManager::BaseManager(const std::string& file_path) : m_ConfigPath(file_path) {}

bool UniConf::Impl::BaseManager::is_initalized() const {
  std::shared_lock<std::shared_mutex> lock(m_RWMutex);
  return m_Initalized;
}
std::string UniConf::Impl::BaseManager::get_config_path() const {
  std::shared_lock<std::shared_mutex> lock(m_RWMutex);
  return m_ConfigPath;
}

void UniConf::Impl::BaseManager::load(const std::string& file_path) {
  std::unique_lock<std::shared_mutex> lock(m_RWMutex);
  if(m_Initalized) return;
  m_ConfigPath = file_path;
  if(!std::filesystem::exists(file_path)) {
    /* TODO: Add the "Get Last Error" feature */
    return;
  }
  load_parser();
  m_Initalized = true;
}

void UniConf::Impl::BaseManager::refresh() {
  load(m_ConfigPath);
}
