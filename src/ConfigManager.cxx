#include <memory>
#include <ConfigManager.hxx>

ConfigManager::Config ConfigManager::Create(const std::string& file_path, ConfigManager::FileType file_type) {
  switch (file_type) {
    case ConfigManager::FileType::TOML:
      return ConfigManager::CreateTomlConfig(file_path);
      break;

    case ConfigManager::FileType::YAML: [[fallthrough]];
    case ConfigManager::FileType::YML:
      [[fallthrough]];

    case ConfigManager::FileType::JSON:
      [[fallthrough]];

    case ConfigManager::FileType::GDBM:
      throw "NOT IMPLEMENTED YET";

    default:
      return ConfigManager::Config();
  }
}
