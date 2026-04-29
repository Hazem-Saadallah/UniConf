#pragma once

#include <memory>
#include <vector>

namespace UniConf {
  namespace Impl {
    class BaseManager;
    class TomlManager;
    class XMLManager;

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
