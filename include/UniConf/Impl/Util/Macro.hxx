#pragma once

// =====================================================================
// Get
// =====================================================================

#define GET_AS_FULL_PATH()                                                                          \
  template<typename T> std::optional<T> get_as(const std::vector<std::string>& full_path) const {   \
    std::shared_lock<std::shared_mutex> lock(m_RWMutex);                                            \
    return get_as_impl<T>(full_path);                                                               \
  }                                                                                                 \
  static_assert(true, "")


#define GET_AS_PATH_KEY()                                                                                             \
  template<typename T> std::optional<T> get_as(const std::vector<std::string>& path, const std::string& key) const {  \
    Datatype::PathType full_path = path;                                                                              \
    full_path.push_back(key);                                                                                         \
    std::shared_lock<std::shared_mutex> lock(m_RWMutex);                                                              \
    return get_as_impl<T>(full_path);                                                                                 \
  }                                                                                                                   \
  static_assert(true, "")

#define GET_AS()      \
  GET_AS_FULL_PATH(); \
  GET_AS_PATH_KEY()

#define GET_TYPE_FULL_PATH_DECLARATION(name, type) std::optional<type> get_##name(const Datatype::PathType& full_path) const override
#define GET_TYPE_PATH_KEY_DECLARATION(name, type) std::optional<type> get_##name(const Datatype::PathType& path, const std::string& key) const override
#define GET_TYPE_DECLARATION(name, type)            \
        GET_TYPE_FULL_PATH_DECLARATION(name, type); \
        GET_TYPE_PATH_KEY_DECLARATION(name, type)

#define GET_TYPE_FULL_PATH_DEFINITION(namespace, name, type)                                                                \
  std::optional<type> namespace::get_##name(const Datatype::PathType& full_path) const { return get_as<type>(full_path); }  \
  static_assert(true, "")
#define GET_TYPE_PATH_KEY_DEFINITION(namespace, name, type)                                                                                   \
  std::optional<type> namespace::get_##name(const Datatype::PathType& path, const std::string& key) const { return get_as<type>(path, key); } \
  static_assert(true, "")
#define GET_TYPE_DEFINITION(namespace, name, type)            \
        GET_TYPE_FULL_PATH_DEFINITION(namespace, name, type); \
        GET_TYPE_PATH_KEY_DEFINITION(namespace, name, type)

#define GET_STRING_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(string, std::string)
#define GET_STRING_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(string, std::string)
#define GET_STRING_DECLARATION() GET_TYPE_DECLARATION(string, std::string)
#define GET_STRING_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, string, std::string)
#define GET_STRING_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, string, std::string)
#define GET_STRING_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, string, std::string)

#define GET_INT8_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(int8, std::int8_t)
#define GET_INT8_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(int8, std::int8_t)
#define GET_INT8_DECLARATION() GET_TYPE_DECLARATION(int8, std::int8_t)
#define GET_INT8_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, int8, std::int8_t)
#define GET_INT8_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, int8, std::int8_t)
#define GET_INT8_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, int8, std::int8_t)

#define GET_UINT8_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(uint8, std::uint8_t)
#define GET_UINT8_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(uint8, std::uint8_t)
#define GET_UINT8_DECLARATION() GET_TYPE_DECLARATION(uint8, std::uint8_t)
#define GET_UINT8_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, uint8, std::uint8_t)
#define GET_UINT8_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, uint8, std::uint8_t)
#define GET_UINT8_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, uint8, std::uint8_t)

#define GET_INT16_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(int16, std::int16_t)
#define GET_INT16_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(int16, std::int16_t)
#define GET_INT16_DECLARATION() GET_TYPE_DECLARATION(int16, std::int16_t)
#define GET_INT16_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, int16, std::int16_t)
#define GET_INT16_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, int16, std::int16_t)
#define GET_INT16_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, int16, std::int16_t)

#define GET_UINT16_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(uint16, std::uint16_t)
#define GET_UINT16_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(uint16, std::uint16_t)
#define GET_UINT16_DECLARATION() GET_TYPE_DECLARATION(uint16, std::uint16_t)
#define GET_UINT16_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, uint16, std::uint16_t)
#define GET_UINT16_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, uint16, std::uint16_t)
#define GET_UINT16_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, uint16, std::uint16_t)

#define GET_INT32_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(int32, std::int32_t)
#define GET_INT32_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(int32, std::int32_t)
#define GET_INT32_DECLARATION() GET_TYPE_DECLARATION(int32, std::int32_t)
#define GET_INT32_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, int32, std::int32_t)
#define GET_INT32_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, int32, std::int32_t)
#define GET_INT32_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, int32, std::int32_t)

#define GET_UINT32_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(uint32, std::uint32_t)
#define GET_UINT32_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(uint32, std::uint32_t)
#define GET_UINT32_DECLARATION() GET_TYPE_DECLARATION(uint32, std::uint32_t)
#define GET_UINT32_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, uint32, std::uint32_t)
#define GET_UINT32_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, uint32, std::uint32_t)
#define GET_UINT32_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, uint32, std::uint32_t)

#define GET_INT64_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(int64, std::int64_t)
#define GET_INT64_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(int64, std::int64_t)
#define GET_INT64_DECLARATION() GET_TYPE_DECLARATION(int64, std::int64_t)
#define GET_INT64_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, int64, std::int64_t)
#define GET_INT64_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, int64, std::int64_t)
#define GET_INT64_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, int64, std::int64_t)

#define GET_UINT64_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(uint64, std::uint64_t)
#define GET_UINT64_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(uint64, std::uint64_t)
#define GET_UINT64_DECLARATION() GET_TYPE_DECLARATION(uint64, std::uint64_t)
#define GET_UINT64_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, uint64, std::uint64_t)
#define GET_UINT64_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, uint64, std::uint64_t)
#define GET_UINT64_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, uint64, std::uint64_t)

#define GET_SIGN_INT_DECLARATIONS()  \
  GET_INT8_DECLARATION();            \
  GET_INT16_DECLARATION();           \
  GET_INT32_DECLARATION();           \
  GET_INT64_DECLARATION()

#define GET_SIGN_INT_DEFINITION(namespace)  \
  GET_INT8_DEFINITION(namespace);           \
  GET_INT16_DEFINITION(namespace);          \
  GET_INT32_DEFINITION(namespace);          \
  GET_INT64_DEFINITION(namespace)

#define GET_USIGN_INT_DECLARATIONS()  \
  GET_UINT8_DECLARATION();            \
  GET_UINT16_DECLARATION();           \
  GET_UINT32_DECLARATION();           \
  GET_UINT64_DECLARATION()

#define GET_USIGN_INT_DEFINITION(namespace)  \
  GET_UINT8_DEFINITION(namespace);           \
  GET_UINT16_DEFINITION(namespace);          \
  GET_UINT32_DEFINITION(namespace);          \
  GET_UINT64_DEFINITION(namespace)

#define GET_INT_DECLARATIONS()  \
  GET_SIGN_INT_DECLARATIONS();  \
  GET_USIGN_INT_DECLARATIONS()  \

#define GET_INT_DEFINITION(namespace)  \
  GET_SIGN_INT_DEFINITION(namespace);  \
  GET_USIGN_INT_DEFINITION(namespace)  \

#define GET_FLOAT32_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(float32, std::float_t)
#define GET_FLOAT32_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(float32, std::float_t)
#define GET_FLOAT32_DECLARATION() GET_TYPE_DECLARATION(float32, std::float_t)
#define GET_FLOAT32_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, float32, std::float_t)
#define GET_FLOAT32_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, float32, std::float_t)
#define GET_FLOAT32_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, float32, std::float_t)

#define GET_FLOAT64_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(float64, std::double_t)
#define GET_FLOAT64_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(float64, std::double_t)
#define GET_FLOAT64_DECLARATION() GET_TYPE_DECLARATION(float64, std::double_t)
#define GET_FLOAT64_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, float64, std::double_t)
#define GET_FLOAT64_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, float64, std::double_t)
#define GET_FLOAT64_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, float64, std::double_t)

#define GET_FLOAT_DECLARATIONS()  \
  GET_FLOAT32_DECLARATION();      \
  GET_FLOAT64_DECLARATION()       \

#define GET_FLOAT_DEFINITION(namespace)  \
  GET_FLOAT32_DEFINITION(namespace);     \
  GET_FLOAT64_DEFINITION(namespace)      \

#define GET_NUMERIC_DECLARATIONS()  \
  GET_INT_DECLARATIONS();           \
  GET_FLOAT_DECLARATIONS()

#define GET_NUMERIC_DEFINITION(namespace)  \
  GET_INT_DEFINITION(namespace);           \
  GET_FLOAT_DEFINITION(namespace)

#define GET_BOOL_FULL_PATH_DECLARATION() GET_TYPE_FULL_PATH_DECLARATION(bool, bool)
#define GET_BOOL_PATH_KEY_DECLARATION() GET_TYPE_PATH_KEY_DECLARATION(bool, bool)
#define GET_BOOL_DECLARATION() GET_TYPE_DECLARATION(bool, bool)
#define GET_BOOL_FULL_PATH_DEFINITION(namespace) GET_TYPE_FULL_PATH_DEFINITION(namespace, bool, bool)
#define GET_BOOL_PATH_KEY_DEFINITION(namespace) GET_TYPE_PATH_KEY_DEFINITION(namespace, bool, bool)
#define GET_BOOL_DEFINITION(namespace) GET_TYPE_DEFINITION(namespace, bool, bool)

#define GET_ALL_DECLARATIONS()    \
  GET_STRING_DECLARATION();       \
  GET_NUMERIC_DECLARATIONS();     \
  GET_BOOL_DECLARATION()

#define GET_ALL_DEFINITION(namespace)    \
  GET_STRING_DEFINITION(namespace);      \
  GET_NUMERIC_DEFINITION(namespace);     \
  GET_BOOL_DEFINITION(namespace)

// =====================================================================
// Set
// =====================================================================

#define SET_AS_FULL_PATH()                                                          \
  template<typename T> void set_as(const Datatype::PathType& full_path, T value) {  \
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);                            \
    set_as_impl(full_path, value);                                                  \
  }                                                                                 \
  static_assert(true, "")

#define SET_AS_PATH_KEY()                                                                              \
  template<typename T> void set_as(const Datatype::PathType& path, const std::string& key, T value) {  \
    Datatype::PathType full_path = path;                                                               \
    full_path.push_back(key);                                                                          \
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);                                               \
    set_as_impl(full_path, value);                                                                     \
  }                                                                                                    \
  static_assert(true, "")

#define SET_AS()      \
  SET_AS_FULL_PATH(); \
  SET_AS_PATH_KEY()

#define SET_TYPE_FULL_PATH_DECLARATION(name, type) void set_##name(const Datatype::PathType& full_path, type value) override
#define SET_TYPE_PATH_KEY_DECLARATION(name, type) void set_##name(const Datatype::PathType& path, const std::string& key, type value) override
#define SET_TYPE_DECLARATION(name, type)            \
        SET_TYPE_FULL_PATH_DECLARATION(name, type); \
        SET_TYPE_PATH_KEY_DECLARATION(name, type)

#define SET_TYPE_FULL_PATH_DEFINITION(namespace, name, type)                                                       \
  void namespace::set_##name(const Datatype::PathType& full_path, type value) { set_as<type>(full_path, value); }  \
  static_assert(true, "")
#define SET_TYPE_PATH_KEY_DEFINITION(namespace, name, type)                                                                          \
  void namespace::set_##name(const Datatype::PathType& path, const std::string& key, type value) { set_as<type>(path, key, value); } \
  static_assert(true, "")
#define SET_TYPE_DEFINITION(namespace, name, type)            \
        SET_TYPE_FULL_PATH_DEFINITION(namespace, name, type); \
        SET_TYPE_PATH_KEY_DEFINITION(namespace, name, type)

#define SET_STRING_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(string, std::string)
#define SET_STRING_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(string, std::string)
#define SET_STRING_DECLARATION() SET_TYPE_DECLARATION(string, std::string)
#define SET_STRING_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, string, std::string)
#define SET_STRING_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, string, std::string)
#define SET_STRING_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, string, std::string)

#define SET_INT8_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(int8, std::int8_t)
#define SET_INT8_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(int8, std::int8_t)
#define SET_INT8_DECLARATION() SET_TYPE_DECLARATION(int8, std::int8_t)
#define SET_INT8_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, int8, std::int8_t)
#define SET_INT8_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, int8, std::int8_t)
#define SET_INT8_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, int8, std::int8_t)

#define SET_UINT8_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(uint8, std::uint8_t)
#define SET_UINT8_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(uint8, std::uint8_t)
#define SET_UINT8_DECLARATION() SET_TYPE_DECLARATION(uint8, std::uint8_t)
#define SET_UINT8_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, uint8, std::uint8_t)
#define SET_UINT8_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, uint8, std::uint8_t)
#define SET_UINT8_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, uint8, std::uint8_t)

#define SET_INT16_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(int16, std::int16_t)
#define SET_INT16_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(int16, std::int16_t)
#define SET_INT16_DECLARATION() SET_TYPE_DECLARATION(int16, std::int16_t)
#define SET_INT16_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, int16, std::int16_t)
#define SET_INT16_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, int16, std::int16_t)
#define SET_INT16_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, int16, std::int16_t)

#define SET_UINT16_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(uint16, std::uint16_t)
#define SET_UINT16_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(uint16, std::uint16_t)
#define SET_UINT16_DECLARATION() SET_TYPE_DECLARATION(uint16, std::uint16_t)
#define SET_UINT16_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, uint16, std::uint16_t)
#define SET_UINT16_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, uint16, std::uint16_t)
#define SET_UINT16_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, uint16, std::uint16_t)

#define SET_INT32_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(int32, std::int32_t)
#define SET_INT32_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(int32, std::int32_t)
#define SET_INT32_DECLARATION() SET_TYPE_DECLARATION(int32, std::int32_t)
#define SET_INT32_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, int32, std::int32_t)
#define SET_INT32_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, int32, std::int32_t)
#define SET_INT32_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, int32, std::int32_t)

#define SET_UINT32_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(uint32, std::uint32_t)
#define SET_UINT32_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(uint32, std::uint32_t)
#define SET_UINT32_DECLARATION() SET_TYPE_DECLARATION(uint32, std::uint32_t)
#define SET_UINT32_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, uint32, std::uint32_t)
#define SET_UINT32_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, uint32, std::uint32_t)
#define SET_UINT32_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, uint32, std::uint32_t)

#define SET_INT64_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(int64, std::int64_t)
#define SET_INT64_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(int64, std::int64_t)
#define SET_INT64_DECLARATION() SET_TYPE_DECLARATION(int64, std::int64_t)
#define SET_INT64_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, int64, std::int64_t)
#define SET_INT64_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, int64, std::int64_t)
#define SET_INT64_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, int64, std::int64_t)

#define SET_UINT64_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(uint64, std::uint64_t)
#define SET_UINT64_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(uint64, std::uint64_t)
#define SET_UINT64_DECLARATION() SET_TYPE_DECLARATION(uint64, std::uint64_t)
#define SET_UINT64_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, uint64, std::uint64_t)
#define SET_UINT64_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, uint64, std::uint64_t)
#define SET_UINT64_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, uint64, std::uint64_t)

#define SET_SIGN_INT_DECLARATIONS()  \
  SET_INT8_DECLARATION();            \
  SET_INT16_DECLARATION();           \
  SET_INT32_DECLARATION();           \
  SET_INT64_DECLARATION()

#define SET_SIGN_INT_DEFINITION(namespace)  \
  SET_INT8_DEFINITION(namespace);           \
  SET_INT16_DEFINITION(namespace);          \
  SET_INT32_DEFINITION(namespace);          \
  SET_INT64_DEFINITION(namespace)

#define SET_USIGN_INT_DECLARATIONS()  \
  SET_UINT8_DECLARATION();            \
  SET_UINT16_DECLARATION();           \
  SET_UINT32_DECLARATION();           \
  SET_UINT64_DECLARATION()

#define SET_USIGN_INT_DEFINITION(namespace)  \
  SET_UINT8_DEFINITION(namespace);           \
  SET_UINT16_DEFINITION(namespace);          \
  SET_UINT32_DEFINITION(namespace);          \
  SET_UINT64_DEFINITION(namespace)

#define SET_INT_DECLARATIONS()  \
  SET_SIGN_INT_DECLARATIONS();  \
  SET_USIGN_INT_DECLARATIONS()

#define SET_INT_DEFINITION(namespace)  \
  SET_SIGN_INT_DEFINITION(namespace);  \
  SET_USIGN_INT_DEFINITION(namespace)  \

#define SET_FLOAT32_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(float32, std::float_t)
#define SET_FLOAT32_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(float32, std::float_t)
#define SET_FLOAT32_DECLARATION() SET_TYPE_DECLARATION(float32, std::float_t)
#define SET_FLOAT32_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, float32, std::float_t)
#define SET_FLOAT32_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, float32, std::float_t)
#define SET_FLOAT32_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, float32, std::float_t)

#define SET_FLOAT64_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(float64, std::double_t)
#define SET_FLOAT64_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(float64, std::double_t)
#define SET_FLOAT64_DECLARATION() SET_TYPE_DECLARATION(float64, std::double_t)
#define SET_FLOAT64_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, float64, std::double_t)
#define SET_FLOAT64_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, float64, std::double_t)
#define SET_FLOAT64_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, float64, std::double_t)

#define SET_FLOAT_DECLARATIONS()  \
  SET_FLOAT32_DECLARATION();      \
  SET_FLOAT64_DECLARATION()       \

#define SET_FLOAT_DEFINITION(namespace)  \
  SET_FLOAT32_DEFINITION(namespace);     \
  SET_FLOAT64_DEFINITION(namespace)      \

#define SET_NUMERIC_DECLARATIONS()  \
  SET_INT_DECLARATIONS();           \
  SET_FLOAT_DECLARATIONS()

#define SET_NUMERIC_DEFINITION(namespace)  \
  SET_INT_DEFINITION(namespace);           \
  SET_FLOAT_DEFINITION(namespace)

#define SET_BOOL_FULL_PATH_DECLARATION() SET_TYPE_FULL_PATH_DECLARATION(bool, bool)
#define SET_BOOL_PATH_KEY_DECLARATION() SET_TYPE_PATH_KEY_DECLARATION(bool, bool)
#define SET_BOOL_DECLARATION() SET_TYPE_DECLARATION(bool, bool)
#define SET_BOOL_FULL_PATH_DEFINITION(namespace) SET_TYPE_FULL_PATH_DEFINITION(namespace, bool, bool)
#define SET_BOOL_PATH_KEY_DEFINITION(namespace) SET_TYPE_PATH_KEY_DEFINITION(namespace, bool, bool)
#define SET_BOOL_DEFINITION(namespace) SET_TYPE_DEFINITION(namespace, bool, bool)

#define SET_ALL_DECLARATIONS()    \
  SET_STRING_DECLARATION();       \
  SET_NUMERIC_DECLARATIONS();     \
  SET_BOOL_DECLARATION()

#define SET_ALL_DEFINITION(namespace)    \
  SET_STRING_DEFINITION(namespace);      \
  SET_NUMERIC_DEFINITION(namespace);     \
  SET_BOOL_DEFINITION(namespace)

// =====================================================================
// Set or Create
// =====================================================================

#define SET_OR_CREATE_AS_FULL_PATH()                                                                  \
  template<typename T> void set_or_create_as(const Datatype::PathType& full_path, const T& value) {   \
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);                                              \
    set_or_create_as_impl(full_path, value);                                                          \
  }                                                                                                   \
  static_assert(true, "")

#define SET_OR_CREATE_AS_PATH_KEY()                                                                                     \
  template<typename T> void set_or_create_as(const Datatype::PathType& path, const std::string& key, const T& value) {  \
    Datatype::PathType full_path = path;                                                                                \
    full_path.push_back(key);                                                                                           \
    std::unique_lock<std::shared_mutex> lock(m_RWMutex);                                                                \
    set_or_create_as_impl(full_path, value);                                                                            \
  }                                                                                                                     \
  static_assert(true, "")

#define SET_OR_CREATE_AS()      \
  SET_OR_CREATE_AS_FULL_PATH(); \
  SET_OR_CREATE_AS_PATH_KEY()

#define SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(name, type) void set_or_create_##name(const Datatype::PathType& full_path, type value) override
#define SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(name, type) void set_or_create_##name(const Datatype::PathType& path, const std::string& key, type value) override
#define SET_OR_CREATE_TYPE_DECLARATION(name, type)            \
        SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(name, type); \
        SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(name, type)

#define SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, name, type)                                                                 \
  void namespace::set_or_create_##name(const Datatype::PathType& full_path, type value) { set_or_create_as<type>(full_path, value); }  \
  static_assert(true, "")
#define SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, name, type)                                                                                    \
  void namespace::set_or_create_##name(const Datatype::PathType& path, const std::string& key, type value) { set_or_create_as<type>(path, key, value); } \
  static_assert(true, "")
#define SET_OR_CREATE_TYPE_DEFINITION(namespace, name, type)            \
        SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, name, type); \
        SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, name, type)

#define SET_OR_CREATE_STRING_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(string, std::string)
#define SET_OR_CREATE_STRING_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(string, std::string)
#define SET_OR_CREATE_STRING_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(string, std::string)
#define SET_OR_CREATE_STRING_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, string, std::string)
#define SET_OR_CREATE_STRING_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, string, std::string)
#define SET_OR_CREATE_STRING_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, string, std::string)

#define SET_OR_CREATE_INT8_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(int8, std::int8_t)
#define SET_OR_CREATE_INT8_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(int8, std::int8_t)
#define SET_OR_CREATE_INT8_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(int8, std::int8_t)
#define SET_OR_CREATE_INT8_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, int8, std::int8_t)
#define SET_OR_CREATE_INT8_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, int8, std::int8_t)
#define SET_OR_CREATE_INT8_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, int8, std::int8_t)

#define SET_OR_CREATE_UINT8_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(uint8, std::uint8_t)
#define SET_OR_CREATE_UINT8_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(uint8, std::uint8_t)
#define SET_OR_CREATE_UINT8_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(uint8, std::uint8_t)
#define SET_OR_CREATE_UINT8_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, uint8, std::uint8_t)
#define SET_OR_CREATE_UINT8_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, uint8, std::uint8_t)
#define SET_OR_CREATE_UINT8_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, uint8, std::uint8_t)

#define SET_OR_CREATE_INT16_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(int16, std::int16_t)
#define SET_OR_CREATE_INT16_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(int16, std::int16_t)
#define SET_OR_CREATE_INT16_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(int16, std::int16_t)
#define SET_OR_CREATE_INT16_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, int16, std::int16_t)
#define SET_OR_CREATE_INT16_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, int16, std::int16_t)
#define SET_OR_CREATE_INT16_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, int16, std::int16_t)

#define SET_OR_CREATE_UINT16_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(uint16, std::uint16_t)
#define SET_OR_CREATE_UINT16_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(uint16, std::uint16_t)
#define SET_OR_CREATE_UINT16_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(uint16, std::uint16_t)
#define SET_OR_CREATE_UINT16_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, uint16, std::uint16_t)
#define SET_OR_CREATE_UINT16_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, uint16, std::uint16_t)
#define SET_OR_CREATE_UINT16_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, uint16, std::uint16_t)

#define SET_OR_CREATE_INT32_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(int32, std::int32_t)
#define SET_OR_CREATE_INT32_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(int32, std::int32_t)
#define SET_OR_CREATE_INT32_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(int32, std::int32_t)
#define SET_OR_CREATE_INT32_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, int32, std::int32_t)
#define SET_OR_CREATE_INT32_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, int32, std::int32_t)
#define SET_OR_CREATE_INT32_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, int32, std::int32_t)

#define SET_OR_CREATE_UINT32_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(uint32, std::uint32_t)
#define SET_OR_CREATE_UINT32_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(uint32, std::uint32_t)
#define SET_OR_CREATE_UINT32_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(uint32, std::uint32_t)
#define SET_OR_CREATE_UINT32_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, uint32, std::uint32_t)
#define SET_OR_CREATE_UINT32_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, uint32, std::uint32_t)
#define SET_OR_CREATE_UINT32_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, uint32, std::uint32_t)

#define SET_OR_CREATE_INT64_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(int64, std::int64_t)
#define SET_OR_CREATE_INT64_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(int64, std::int64_t)
#define SET_OR_CREATE_INT64_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(int64, std::int64_t)
#define SET_OR_CREATE_INT64_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, int64, std::int64_t)
#define SET_OR_CREATE_INT64_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, int64, std::int64_t)
#define SET_OR_CREATE_INT64_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, int64, std::int64_t)

#define SET_OR_CREATE_UINT64_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(uint64, std::uint64_t)
#define SET_OR_CREATE_UINT64_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(uint64, std::uint64_t)
#define SET_OR_CREATE_UINT64_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(uint64, std::uint64_t)
#define SET_OR_CREATE_UINT64_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, uint64, std::uint64_t)
#define SET_OR_CREATE_UINT64_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, uint64, std::uint64_t)
#define SET_OR_CREATE_UINT64_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, uint64, std::uint64_t)

#define SET_OR_CREATE_SIGN_INT_DECLARATIONS()  \
  SET_OR_CREATE_INT8_DECLARATION();            \
  SET_OR_CREATE_INT16_DECLARATION();           \
  SET_OR_CREATE_INT32_DECLARATION();           \
  SET_OR_CREATE_INT64_DECLARATION()

#define SET_OR_CREATE_SIGN_INT_DEFINITION(namespace)  \
  SET_OR_CREATE_INT8_DEFINITION(namespace);           \
  SET_OR_CREATE_INT16_DEFINITION(namespace);          \
  SET_OR_CREATE_INT32_DEFINITION(namespace);          \
  SET_OR_CREATE_INT64_DEFINITION(namespace)

#define SET_OR_CREATE_USIGN_INT_DECLARATIONS()  \
  SET_OR_CREATE_UINT8_DECLARATION();            \
  SET_OR_CREATE_UINT16_DECLARATION();           \
  SET_OR_CREATE_UINT32_DECLARATION();           \
  SET_OR_CREATE_UINT64_DECLARATION()

#define SET_OR_CREATE_USIGN_INT_DEFINITION(namespace)  \
  SET_OR_CREATE_UINT8_DEFINITION(namespace);           \
  SET_OR_CREATE_UINT16_DEFINITION(namespace);          \
  SET_OR_CREATE_UINT32_DEFINITION(namespace);          \
  SET_OR_CREATE_UINT64_DEFINITION(namespace)

#define SET_OR_CREATE_INT_DECLARATIONS()  \
  SET_OR_CREATE_SIGN_INT_DECLARATIONS();  \
  SET_OR_CREATE_USIGN_INT_DECLARATIONS()  \

#define SET_OR_CREATE_INT_DEFINITION(namespace)  \
  SET_OR_CREATE_SIGN_INT_DEFINITION(namespace);  \
  SET_OR_CREATE_USIGN_INT_DEFINITION(namespace)  \

#define SET_OR_CREATE_FLOAT32_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(float32, std::float_t)
#define SET_OR_CREATE_FLOAT32_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(float32, std::float_t)
#define SET_OR_CREATE_FLOAT32_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(float32, std::float_t)
#define SET_OR_CREATE_FLOAT32_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, float32, std::float_t)
#define SET_OR_CREATE_FLOAT32_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, float32, std::float_t)
#define SET_OR_CREATE_FLOAT32_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, float32, std::float_t)

#define SET_OR_CREATE_FLOAT64_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(float64, std::double_t)
#define SET_OR_CREATE_FLOAT64_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(float64, std::double_t)
#define SET_OR_CREATE_FLOAT64_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(float64, std::double_t)
#define SET_OR_CREATE_FLOAT64_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, float64, std::double_t)
#define SET_OR_CREATE_FLOAT64_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, float64, std::double_t)
#define SET_OR_CREATE_FLOAT64_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, float64, std::double_t)

#define SET_OR_CREATE_FLOAT_DECLARATIONS()  \
  SET_OR_CREATE_FLOAT32_DECLARATION();      \
  SET_OR_CREATE_FLOAT64_DECLARATION()       \

#define SET_OR_CREATE_FLOAT_DEFINITION(namespace)  \
  SET_OR_CREATE_FLOAT32_DEFINITION(namespace);     \
  SET_OR_CREATE_FLOAT64_DEFINITION(namespace)      \

#define SET_OR_CREATE_NUMERIC_DECLARATIONS()  \
  SET_OR_CREATE_INT_DECLARATIONS();           \
  SET_OR_CREATE_FLOAT_DECLARATIONS()

#define SET_OR_CREATE_NUMERIC_DEFINITION(namespace)  \
  SET_OR_CREATE_INT_DEFINITION(namespace);           \
  SET_OR_CREATE_FLOAT_DEFINITION(namespace)

#define SET_OR_CREATE_BOOL_FULL_PATH_DECLARATION() SET_OR_CREATE_TYPE_FULL_PATH_DECLARATION(bool, bool)
#define SET_OR_CREATE_BOOL_PATH_KEY_DECLARATION() SET_OR_CREATE_TYPE_PATH_KEY_DECLARATION(bool, bool)
#define SET_OR_CREATE_BOOL_DECLARATION() SET_OR_CREATE_TYPE_DECLARATION(bool, bool)
#define SET_OR_CREATE_BOOL_FULL_PATH_DEFINITION(namespace) SET_OR_CREATE_TYPE_FULL_PATH_DEFINITION(namespace, bool, bool)
#define SET_OR_CREATE_BOOL_PATH_KEY_DEFINITION(namespace) SET_OR_CREATE_TYPE_PATH_KEY_DEFINITION(namespace, bool, bool)
#define SET_OR_CREATE_BOOL_DEFINITION(namespace) SET_OR_CREATE_TYPE_DEFINITION(namespace, bool, bool)

#define SET_OR_CREATE_ALL_DECLARATIONS()    \
  SET_OR_CREATE_STRING_DECLARATION();       \
  SET_OR_CREATE_NUMERIC_DECLARATIONS();     \
  SET_OR_CREATE_BOOL_DECLARATION()

#define SET_OR_CREATE_ALL_DEFINITION(namespace)    \
  SET_OR_CREATE_STRING_DEFINITION(namespace);      \
  SET_OR_CREATE_NUMERIC_DEFINITION(namespace);     \
  SET_OR_CREATE_BOOL_DEFINITION(namespace)
