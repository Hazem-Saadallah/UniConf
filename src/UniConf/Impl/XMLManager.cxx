#include <format>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <optional>
#include <UniConf/Impl/Util/Misc.hxx>
#include <UniConf/Impl/XMLManager.hxx>
#include <vector>

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

std::optional<std::string> UniConf::Impl::XMLManager::get_string(const std::vector<std::string>& full_path) const { return get_as<std::string>(full_path); }
std::optional<std::string> UniConf::Impl::XMLManager::get_string(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::string>(path, key); }

std::optional<std::int8_t> UniConf::Impl::XMLManager::get_int8(const std::vector<std::string>& full_path) const { return get_as<std::int8_t>(full_path); }
std::optional<std::int8_t> UniConf::Impl::XMLManager::get_int8(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int8_t>(path, key); }

std::optional<std::uint8_t> UniConf::Impl::XMLManager::get_uint8(const std::vector<std::string>& full_path) const { return get_as<std::uint8_t>(full_path); }
std::optional<std::uint8_t> UniConf::Impl::XMLManager::get_uint8(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint8_t>(path, key); }

std::optional<std::int16_t> UniConf::Impl::XMLManager::get_int16(const std::vector<std::string>& full_path) const { return get_as<std::int16_t>(full_path); }
std::optional<std::int16_t> UniConf::Impl::XMLManager::get_int16(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int16_t>(path, key); }

std::optional<std::uint16_t> UniConf::Impl::XMLManager::get_uint16(const std::vector<std::string>& full_path) const { return get_as<std::uint16_t>(full_path); }
std::optional<std::uint16_t> UniConf::Impl::XMLManager::get_uint16(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint16_t>(path, key); }

std::optional<std::int32_t> UniConf::Impl::XMLManager::get_int32(const std::vector<std::string>& full_path) const { return get_as<std::int32_t>(full_path); }
std::optional<std::int32_t> UniConf::Impl::XMLManager::get_int32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int32_t>(path, key); }

std::optional<std::uint32_t> UniConf::Impl::XMLManager::get_uint32(const std::vector<std::string>& full_path) const { return get_as<std::uint32_t>(full_path); }
std::optional<std::uint32_t> UniConf::Impl::XMLManager::get_uint32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint32_t>(path, key); }

std::optional<std::int64_t> UniConf::Impl::XMLManager::get_int64(const std::vector<std::string>& full_path) const { return get_as<std::int64_t>(full_path); }
std::optional<std::int64_t> UniConf::Impl::XMLManager::get_int64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::int64_t>(path, key); }

std::optional<std::uint64_t> UniConf::Impl::XMLManager::get_uint64(const std::vector<std::string>& full_path) const { return get_as<std::uint64_t>(full_path); }
std::optional<std::uint64_t> UniConf::Impl::XMLManager::get_uint64(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::uint64_t>(path, key); }

std::optional<std::float_t> UniConf::Impl::XMLManager::get_float32(const std::vector<std::string>& full_path) const { return get_as<std::float_t>(full_path); }
std::optional<std::float_t> UniConf::Impl::XMLManager::get_float32(const std::vector<std::string>& path, const std::string& key) const { return get_as<std::float_t>(path, key); }

std::optional<std::double_t> UniConf::Impl::XMLManager::get_float64(const std::vector<std::string>& full_path) const { return get_as<std::double_t>(full_path); }
std::optional<std::double_t> UniConf::Impl::XMLManager::get_float64(const std::vector<std::string>& path, const std::string& key) const { return get_as<double_t>(path, key); }

std::optional<bool> UniConf::Impl::XMLManager::get_bool(const std::vector<std::string>& full_path) const { return get_as<bool>(full_path); }
std::optional<bool> UniConf::Impl::XMLManager::get_bool(const std::vector<std::string>& path, const std::string& key) const { return get_as<bool>(path, key); }

bool UniConf::Impl::XMLManager::path_exists(const std::vector<std::string>& path) const { return navigate_parents(path, false) != std::nullopt; }
void UniConf::Impl::XMLManager::create_table(const std::vector<std::string>& path) { navigate_parents(path, true); }

void UniConf::Impl::XMLManager::set_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_as<std::string>(path, key, value); }
void UniConf::Impl::XMLManager::set_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) { set_as<std::int8_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) { set_as<std::uint8_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) { set_as<std::int16_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) { set_as<std::uint16_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) { set_as<std::int32_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) { set_as<std::uint32_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_as<std::int64_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) { set_as<std::uint64_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) { set_as<std::float_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_as<std::double_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_as<bool>(path, key, value); }

void UniConf::Impl::XMLManager::set_or_create_string(const std::vector<std::string>& path, const std::string& key, const std::string& value) { set_or_create_as<std::string>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_int8(const std::vector<std::string>& path, const std::string& key, std::int8_t value) { set_or_create_as<std::int8_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_uint8(const std::vector<std::string>& path, const std::string& key, std::uint8_t value) { set_or_create_as<std::uint8_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_int16(const std::vector<std::string>& path, const std::string& key, std::int16_t value) { set_or_create_as<std::int16_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_uint16(const std::vector<std::string>& path, const std::string& key, std::uint16_t value) { set_or_create_as<std::uint16_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_int32(const std::vector<std::string>& path, const std::string& key, std::int32_t value) { set_or_create_as<std::int32_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_uint32(const std::vector<std::string>& path, const std::string& key, std::uint32_t value) { set_or_create_as<std::uint32_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_int64(const std::vector<std::string>& path, const std::string& key, std::int64_t value) { set_or_create_as<std::int64_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_uint64(const std::vector<std::string>& path, const std::string& key, std::uint64_t value) { set_or_create_as<std::uint64_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_float32(const std::vector<std::string>& path, const std::string& key, std::float_t value) { set_or_create_as<std::float_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_float64(const std::vector<std::string>& path, const std::string& key, std::double_t value) { set_or_create_as<std::double_t>(path, key, value); }
void UniConf::Impl::XMLManager::set_or_create_bool(const std::vector<std::string>& path, const std::string& key, bool value) { set_or_create_as<bool>(path, key, value); }
