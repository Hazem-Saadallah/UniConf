#include <BaseManager.hxx>

Impl::BaseManager::BaseManager(const std::string& file_path) : m_ConfigPath(file_path) {}

bool Impl::BaseManager::is_initalized() { return m_Initalized; }
std::string Impl::BaseManager::get_config_path() { return m_ConfigPath; }
