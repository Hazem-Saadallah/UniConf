#pragma once

#include <mutex>
#include <optional>
#include <shared_mutex>
#include <UniConf/Impl/datatypes.hxx>
#include <UniConf/Impl/BaseManager.hxx>

namespace UniConf {
  namespace Impl {
    template<typename ValueType> class Value {
    private:
      UniConf::Impl::Datatype::Config m_Config=nullptr;
      UniConf::Impl::Datatype::PathType m_Path={};
      ValueType m_Default=ValueType();
      mutable std::shared_mutex m_RWMutex;

    public:
      Value() = default;
      Value(UniConf::Impl::Datatype::Config config, UniConf::Impl::Datatype::PathType path, ValueType default_value) : m_Config(config), m_Path(path), m_Default(default_value) {}
      ~Value() = default;
      Value(Value&& other) noexcept = default;
      Value &operator=(Value&& other) noexcept = default;
      Value(const Value& other) = default;
      Value &operator=(const Value& other) = default;

    public:
      std::optional<ValueType> get_value() const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        return m_Config->get_as<ValueType>(m_Path);
      }
      ValueType get_value_or_default() const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        return m_Config->get_as<ValueType>(m_Path).value_or(m_Default);
      }
      void set_value(ValueType value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        m_Config->set_as<ValueType>(m_Path, value);
      }

      ValueType get_default() const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        return m_Default;
      };
      void set_default(ValueType value) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        m_Default = value;
      }

      UniConf::Impl::Datatype::PathType get_path() const {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        return m_Path;
      }
      void set_path(UniConf::Impl::Datatype::PathType path) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        m_Path = path;
      }

      UniConf::Impl::Datatype::Config get_config() {
        std::shared_lock<std::shared_mutex> lock(m_RWMutex);
        return m_Config;
      }
      void set_config(UniConf::Impl::Datatype::Config config) {
        std::unique_lock<std::shared_mutex> lock(m_RWMutex);
        m_Config = config;
      }
    };
  }
}
