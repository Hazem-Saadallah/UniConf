#include <mutex>
#include <vector>
#include <format>
#include <string>
#include <optional>
#include <shared_mutex>
#include <UniConf/Impl/Util/Misc.hxx>
#include <UniConf/Impl/XMLManager.hxx>
#include <UniConf/Impl/Util/Macro.hxx>

UniConf::Impl::XMLManager::XMLManager(const std::string& file_path) : UniConf::Impl::BaseManager(file_path) {
  load(file_path);
}

void UniConf::Impl::XMLManager::load_parser() {
  pugi::xml_parse_result result = m_Document.load_file(m_ConfigPath.c_str());
  /* TODO: Add error handling*/
}

void UniConf::Impl::XMLManager::save(std::optional<std::string> file_path) {
  std::unique_lock<std::shared_mutex> lock(m_RWMutex);
  m_Document.save_file(file_path.value_or(std::format("./{}", Util::Misc::generate_random_string(5, "UniConf_XML_", ".xml"))).c_str());
}

std::optional<pugi::xml_node> UniConf::Impl::XMLManager::navigate_parents(std::span<const std::string> path, bool create_missing) const {
  if (path.empty()) return std::nullopt;
  pugi::xml_node current = m_Document;
  for (size_t i = 0; i < path.size(); ++i) {
    pugi::xml_node next = current.child(path[i].c_str());
      if (!next) {
        if (create_missing) next = current.append_child(path[i].c_str());
        else return std::nullopt;
      }
      current = next;
    }
  return current;
}


bool UniConf::Impl::XMLManager::path_exists(const std::vector<std::string>& path) const { return navigate_parents(path, false) != std::nullopt; }
void UniConf::Impl::XMLManager::create_table(const std::vector<std::string>& path) { navigate_parents(path, true); }

GET_ALL_DEFINITION(UniConf::Impl::XMLManager);
SET_ALL_DEFINITION(UniConf::Impl::XMLManager);
SET_OR_CREATE_ALL_DEFINITION(UniConf::Impl::XMLManager);
