#include <mutex>
#include <filesystem>
#include <UniConf/Impl/BaseManager.hxx>

UniConf::Impl::BaseManager::BaseManager(const std::string& file_path) : m_ConfigPath(file_path) {}

bool UniConf::Impl::BaseManager::is_initalized() const {
  std::shared_lock<std::shared_mutex> lock(m_RWMutex);
  return m_Initalized;
}
std::string UniConf::Impl::BaseManager::get_config_path() const {
  std::shared_lock<std::shared_mutex> lock(m_RWMutex);
  return m_ConfigPath;
}

void UniConf::Impl::BaseManager::load(const std::string& file_path) {
  std::unique_lock<std::shared_mutex> lock(m_RWMutex);
  if(m_Initalized) return;
  m_ConfigPath = file_path;
  if(!std::filesystem::exists(file_path)) {
    /* TODO: Add the "Get Last Error" feature */
    return;
  }
  load_parser();
  m_Initalized = true;
}

void UniConf::Impl::BaseManager::refresh() {
  load(m_ConfigPath);
}


template<> std::optional<std::string> UniConf::Impl::BaseManager::get_as<std::string>(const std::vector<std::string>& full_path) const { return get_string(full_path); }
template<> std::optional<std::string> UniConf::Impl::BaseManager::get_as<std::string>(const std::vector<std::string>& path, const std::string& key) const { return get_string(path, key); }

template<> std::optional<std::int8_t> UniConf::Impl::BaseManager::get_as<std::int8_t>(const std::vector<std::string>& full_path) const { return get_int8(full_path); }
template<> std::optional<std::int8_t> UniConf::Impl::BaseManager::get_as<std::int8_t>(const std::vector<std::string>& path, const std::string& key) const { return get_int8(path, key); }
template<> std::optional<std::uint8_t> UniConf::Impl::BaseManager::get_as<std::uint8_t>(const std::vector<std::string>& full_path) const { return get_uint8(full_path); }
template<> std::optional<std::uint8_t> UniConf::Impl::BaseManager::get_as<std::uint8_t>(const std::vector<std::string>& path, const std::string& key) const { return get_uint8(path, key); }

template<> std::optional<std::int16_t> UniConf::Impl::BaseManager::get_as<std::int16_t>(const std::vector<std::string>& full_path) const { return get_int16(full_path); }
template<> std::optional<std::int16_t> UniConf::Impl::BaseManager::get_as<std::int16_t>(const std::vector<std::string>& path, const std::string& key) const { return get_int16(path, key); }
template<> std::optional<std::uint16_t> UniConf::Impl::BaseManager::get_as<std::uint16_t>(const std::vector<std::string>& full_path) const { return get_uint16(full_path); }
template<> std::optional<std::uint16_t> UniConf::Impl::BaseManager::get_as<std::uint16_t>(const std::vector<std::string>& path, const std::string& key) const { return get_uint16(path, key); }

template<> std::optional<std::int32_t> UniConf::Impl::BaseManager::get_as<std::int32_t>(const std::vector<std::string>& full_path) const { return get_int32(full_path); }
template<> std::optional<std::int32_t> UniConf::Impl::BaseManager::get_as<std::int32_t>(const std::vector<std::string>& path, const std::string& key) const { return get_int32(path, key); }
template<> std::optional<std::uint32_t> UniConf::Impl::BaseManager::get_as<std::uint32_t>(const std::vector<std::string>& full_path) const { return get_uint32(full_path); }
template<> std::optional<std::uint32_t> UniConf::Impl::BaseManager::get_as<std::uint32_t>(const std::vector<std::string>& path, const std::string& key) const { return get_uint32(path, key); }

template<> std::optional<std::int64_t> UniConf::Impl::BaseManager::get_as<std::int64_t>(const std::vector<std::string>& full_path) const { return get_int64(full_path); }
template<> std::optional<std::int64_t> UniConf::Impl::BaseManager::get_as<std::int64_t>(const std::vector<std::string>& path, const std::string& key) const { return get_int64(path, key); }
template<> std::optional<std::uint64_t> UniConf::Impl::BaseManager::get_as<std::uint64_t>(const std::vector<std::string>& full_path) const { return get_uint64(full_path); }
template<> std::optional<std::uint64_t> UniConf::Impl::BaseManager::get_as<std::uint64_t>(const std::vector<std::string>& path, const std::string& key) const { return get_uint64(path, key); }

template<> std::optional<std::float_t> UniConf::Impl::BaseManager::get_as<std::float_t>(const std::vector<std::string>& full_path) const { return get_float32(full_path); }
template<> std::optional<std::float_t> UniConf::Impl::BaseManager::get_as<std::float_t>(const std::vector<std::string>& path, const std::string& key) const { return get_float32(path, key); }
template<> std::optional<std::double_t> UniConf::Impl::BaseManager::get_as<std::double_t>(const std::vector<std::string>& full_path) const { return get_float64(full_path); }
template<> std::optional<std::double_t> UniConf::Impl::BaseManager::get_as<std::double_t>(const std::vector<std::string>& path, const std::string& key) const { return get_float64(path, key); }

template<> std::optional<bool> UniConf::Impl::BaseManager::get_as<bool>(const std::vector<std::string>& full_path) const { return get_bool(full_path); }
template<> std::optional<bool> UniConf::Impl::BaseManager::get_as<bool>(const std::vector<std::string>& path, const std::string& key) const { return get_bool(path, key); }

template<> void UniConf::Impl::BaseManager::set_as<std::string>(const std::vector<std::string>& path, const std::string& key, const std::string& value) { return set_string(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::int8_t>(const std::vector<std::string>& path, const std::string& key, const std::int8_t& value) { return set_int8(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::uint8_t>(const std::vector<std::string>& path, const std::string& key, const std::uint8_t& value) { return set_uint8(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::int16_t>(const std::vector<std::string>& path, const std::string& key, const std::int16_t& value) { return set_int16(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::uint16_t>(const std::vector<std::string>& path, const std::string& key, const std::uint16_t& value) { return set_uint16(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::int32_t>(const std::vector<std::string>& path, const std::string& key, const std::int32_t& value) { return set_int32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::uint32_t>(const std::vector<std::string>& path, const std::string& key, const std::uint32_t& value) { return set_uint32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::int64_t>(const std::vector<std::string>& path, const std::string& key, const std::int64_t& value) { return set_int64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::uint64_t>(const std::vector<std::string>& path, const std::string& key, const std::uint64_t& value) { return set_uint64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::float_t>(const std::vector<std::string>& path, const std::string& key, const std::float_t& value) { return set_float32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<std::double_t>(const std::vector<std::string>& path, const std::string& key, const std::double_t& value) { return set_float64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_as<bool>(const std::vector<std::string>& path, const std::string& key, const bool& value) { return set_bool(path, key, value); }

template<> void UniConf::Impl::BaseManager::set_or_create_as<std::string>(const std::vector<std::string>& path, const std::string& key, const std::string& value) { return set_or_create_string(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::int8_t>(const std::vector<std::string>& path, const std::string& key, const std::int8_t& value) { return set_or_create_int8(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::uint8_t>(const std::vector<std::string>& path, const std::string& key, const std::uint8_t& value) { return set_or_create_uint8(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::int16_t>(const std::vector<std::string>& path, const std::string& key, const std::int16_t& value) { return set_or_create_int16(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::uint16_t>(const std::vector<std::string>& path, const std::string& key, const std::uint16_t& value) { return set_or_create_uint16(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::int32_t>(const std::vector<std::string>& path, const std::string& key, const std::int32_t& value) { return set_or_create_int32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::uint32_t>(const std::vector<std::string>& path, const std::string& key, const std::uint32_t& value) { return set_or_create_uint32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::int64_t>(const std::vector<std::string>& path, const std::string& key, const std::int64_t& value) { return set_or_create_int64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::uint64_t>(const std::vector<std::string>& path, const std::string& key, const std::uint64_t& value) { return set_or_create_uint64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::float_t>(const std::vector<std::string>& path, const std::string& key, const std::float_t& value) { return set_or_create_float32(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<std::double_t>(const std::vector<std::string>& path, const std::string& key, const std::double_t& value) { return set_or_create_float64(path, key, value); }
template<> void UniConf::Impl::BaseManager::set_or_create_as<bool>(const std::vector<std::string>& path, const std::string& key, const bool& value) { return set_or_create_bool(path, key, value); }
