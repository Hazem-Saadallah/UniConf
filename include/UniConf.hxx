#pragma once 

#include <string>
#include <memory>
#include <UniConf/Impl/datatypes.hxx>
#include <UniConf/Impl/BaseManager.hxx>
#include <UniConf/Impl/TomlManager.hxx>
#include <UniConf/Impl/XMLManager.hxx>
#include <UniConf/Impl/Value.hxx>

namespace UniConf {
  typedef UniConf::Impl::Datatype::Config Config;
  typedef UniConf::Impl::Datatype::TomlConfig TomlConfig;
  typedef UniConf::Impl::Datatype::XMLConfig XMLConfig;
  typedef UniConf::Impl::Datatype::PathType PathType;
  typedef UniConf::Impl::Datatype::FileType FileType;
  template <typename T> using Value = UniConf::Impl::Value<T>;

  UniConf::Impl::Datatype::Config Create(const std::string& file_path, UniConf::Impl::Datatype::FileType file_type);

  template<typename... T> inline UniConf::Impl::Datatype::TomlConfig CreateTomlConfig(T&&... args) {
    return std::make_unique<UniConf::Impl::TomlManager>(std::forward<T>(args)...);
  }

  template<typename... T> inline UniConf::Impl::Datatype::XMLConfig CreateXMLConfig(T&&... args) {
    return std::make_unique<UniConf::Impl::XMLManager>(std::forward<T>(args)...);
  }
};
