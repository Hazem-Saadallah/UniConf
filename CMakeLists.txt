include(FetchContent)
CMAKE_MINIMUM_REQUIRED(VERSION 3.31)
project(UniConf LANGUAGES C CXX)

option(BUILD_TESTS "Build the main.cxx test executable" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BIN_NAME bin.out)
set(COMMON_COMPILE_OPTIONS -Wall -Wextra)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/BaseManager.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/TomlManager.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/src/UniConf.cxx
)
set(COMMON_LIBS
  tomlplusplus::tomlplusplus
)

set(COMMON_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

FetchContent_Declare(
  tomlplusplus
  URL https://github.com/marzer/tomlplusplus/archive/refs/tags/v3.4.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP true
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/tomlplusplus
  BINARY_DIR ${CMAKE_BINARY_DIR}/extern/tomlplusplus
)

FetchContent_MakeAvailable(tomlplusplus)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${COMMON_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})

if(BUILD_TESTS)
  add_executable(${BIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx)
  target_link_libraries(${BIN_NAME} PRIVATE ${PROJECT_NAME})
  target_include_directories(${BIN_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
endif()
