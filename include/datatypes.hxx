#pragma once

#include <memory>
#include <BaseManager.hxx>
#include <TomlManager.hxx>

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

    typedef std::unique_ptr<BaseManager> Config;
    typedef std::unique_ptr<TomlManager> TomlConfig;
    typedef std::vector<std::string> PathType;
  }
}
