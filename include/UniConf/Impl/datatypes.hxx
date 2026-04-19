#pragma once

#include <memory>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/TomlManager.hxx>
#include <UniConf/Impl/XMLManager.hxx>

namespace UniConf {
  namespace Impl {
    namespace Datatype {
      enum class FileType {
        TOML=0,
        YAML,
        YML,
        JSON,
        XML,
        GDBM
      };

      typedef std::shared_ptr<BaseManager> Config;
      typedef std::shared_ptr<TomlManager> TomlConfig;
      typedef std::shared_ptr<XMLManager> XMLConfig;
      typedef std::vector<std::string> PathType;
    }
  }
}
