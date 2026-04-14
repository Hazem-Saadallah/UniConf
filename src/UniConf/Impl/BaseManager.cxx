#include <UniConf/Impl/BaseManager.hxx>

UniConf::Impl::BaseManager::BaseManager(const std::string& file_path) : m_ConfigPath(file_path) {}

bool UniConf::Impl::BaseManager::is_initalized() { return m_Initalized; }
std::string UniConf::Impl::BaseManager::get_config_path() { return m_ConfigPath; }
