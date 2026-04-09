#include <UniConf.hxx>

Impl::Datatype::Config UniConf::Create(const std::string& file_path, Impl::Datatype::FileType file_type) {
  switch (file_type) {
    case Impl::Datatype::FileType::TOML:
      return UniConf::CreateTomlConfig(file_path);
      break;

    case Impl::Datatype::FileType::YAML: [[fallthrough]];
    case Impl::Datatype::FileType::YML:
      [[fallthrough]];

    case Impl::Datatype::FileType::JSON:
      [[fallthrough]];

    case Impl::Datatype::FileType::XML:
      [[fallthrough]];

    case Impl::Datatype::FileType::GDBM:
      throw "NOT IMPLEMENTED YET";

    default:
      return Impl::Datatype::Config();
  }
}
