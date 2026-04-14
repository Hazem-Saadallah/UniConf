#include <datatypes.hxx>
#include <UniConf.hxx>

UniConf::Impl::Datatype::Config UniConf::Create(const std::string& file_path, Impl::Datatype::FileType file_type) {
  switch (file_type) {
    case UniConf::Impl::Datatype::FileType::TOML:
      return UniConf::CreateTomlConfig(file_path);
      break;

    case UniConf::Impl::Datatype::FileType::YAML: [[fallthrough]];
    case UniConf::Impl::Datatype::FileType::YML:
      [[fallthrough]];

    case UniConf::Impl::Datatype::FileType::JSON:
      [[fallthrough]];

    case UniConf::Impl::Datatype::FileType::XML:
      [[fallthrough]];

    case UniConf::Impl::Datatype::FileType::GDBM:
      throw "NOT IMPLEMENTED YET";

    default:
      return UniConf::Impl::Datatype::Config();
  }
}
