#pragma once 

#include "TomlManager.hxx"
#include <memory>
#include <BaseManager.hxx>

namespace ConfigManager {
  enum class FileType {
    TOML=0,
    YAML,
    YML,
    JSON,
    GDBM
  };

  typedef std::unique_ptr<IBaseManager> Config;
  typedef std::unique_ptr<ITomlManager> TomlConfig;

  Config Create(const std::string& file_path, FileType file_type);

  template<typename... T> inline TomlConfig CreateTomlConfig(T&&... args) {
    return std::make_unique<ITomlManager>(std::forward<T>(args)...);
  }
};
