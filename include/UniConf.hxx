#pragma once 

#include <concepts>
#include <string>
#include <vector>
#include <memory>
#include <datatypes.hxx>
#include <TomlManager.hxx>
#include <BaseManager.hxx>

namespace UniConf {
  typedef Impl::Datatype::Config Config;
  typedef Impl::Datatype::TomlConfig TomlConfig;
  typedef Impl::Datatype::PathType PathType;
  typedef Impl::Datatype::FileType FileType;

  Impl::Datatype::Config Create(const std::string& file_path, Impl::Datatype::FileType file_type);

  template<typename... T> inline Impl::Datatype::TomlConfig CreateTomlConfig(T&&... args) {
    return std::make_unique<Impl::TomlManager>(std::forward<T>(args)...);
  }
};
