#include <BaseManager.hxx>

IBaseManager::IBaseManager(const std::string& file_path) : m_ConfigPath(file_path) {}

bool IBaseManager::is_initalized() { return m_Initalized; }
std::string IBaseManager::get_config_path() { return m_ConfigPath; }
