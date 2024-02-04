cmake_minimum_required(VERSION 3.19)

project(i18n_tests CXX)
include(CTest)

enable_testing()
include(FetchContent)

message(STATUS "Downloading catch2")
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 05e10dfccc28c7f973727c54f850237d07d5e10f # v3.5.2
)
FetchContent_MakeAvailable(Catch2)

message(STATUS "Downloading nlohmann/json")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG 9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03 # v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

message(STATUS "Downloading rapidjson")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_THIRDPARTY_GTEST OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX11 OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX17 ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    RapidJSON
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG 6089180ecb704cb2b136777798fa1be303618975
)
FetchContent_MakeAvailable(RapidJSON)
set(RAPIDJSON_INCLUDE_DIRS ${RapidJSON_SOURCE_DIR}/include)

message(STATUS "Downloading lua")
PROJECT(lua
   LANGUAGES C
)
FetchContent_Declare(
    Lua
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG 6443185167c77adcc8552a3fee7edab7895db1a9 # v5.4.6
)
FetchContent_MakeAvailable(Lua)
set(Lua_SOURCE_DIR ${CMAKE_SOURCE_DIR}/build/_deps/lua-src)
set(LUA_INCLUDE_DIRS ${Lua_SOURCE_DIR})

add_library(lua
  ${Lua_SOURCE_DIR}/lapi.c
  ${Lua_SOURCE_DIR}/lauxlib.c
  ${Lua_SOURCE_DIR}/lbaselib.c
  ${Lua_SOURCE_DIR}/lcode.c
  ${Lua_SOURCE_DIR}/lcorolib.c
  ${Lua_SOURCE_DIR}/lctype.c
  ${Lua_SOURCE_DIR}/ldblib.c
  ${Lua_SOURCE_DIR}/ldebug.c
  ${Lua_SOURCE_DIR}/ldo.c
  ${Lua_SOURCE_DIR}/ldump.c
  ${Lua_SOURCE_DIR}/lfunc.c
  ${Lua_SOURCE_DIR}/lgc.c
  ${Lua_SOURCE_DIR}/linit.c
  ${Lua_SOURCE_DIR}/liolib.c
  ${Lua_SOURCE_DIR}/llex.c
  ${Lua_SOURCE_DIR}/lmathlib.c
  ${Lua_SOURCE_DIR}/lmem.c
  ${Lua_SOURCE_DIR}/loadlib.c
  ${Lua_SOURCE_DIR}/lobject.c
  ${Lua_SOURCE_DIR}/lopcodes.c
  ${Lua_SOURCE_DIR}/loslib.c
  ${Lua_SOURCE_DIR}/lparser.c
  ${Lua_SOURCE_DIR}/lstate.c
  ${Lua_SOURCE_DIR}/lstring.c
  ${Lua_SOURCE_DIR}/lstrlib.c
  ${Lua_SOURCE_DIR}/ltable.c
  ${Lua_SOURCE_DIR}/ltablib.c
  ${Lua_SOURCE_DIR}/ltests.c
  ${Lua_SOURCE_DIR}/ltm.c
  ${Lua_SOURCE_DIR}/lua.c
  ${Lua_SOURCE_DIR}/lundump.c
  ${Lua_SOURCE_DIR}/lutf8lib.c
  ${Lua_SOURCE_DIR}/lvm.c
  ${Lua_SOURCE_DIR}/lzio.c
)
add_library(lua::lua ALIAS lua)

if (WIN32)
  target_compile_definitions(lua PRIVATE LUA_USE_WINDOWS)
endif()

target_include_directories(lua PUBLIC lua)
if (UNIX)
  target_compile_definitions(lua PRIVATE LUA_USE_LINUX)
  target_link_libraries(lua PRIVATE dl)
endif()

message(STATUS "Downloading sol2")
set(SOL2_BUILD_LUA FALSE CACHE BOOL "Always build Lua, do not search for it in the system")
FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG dca62a0f02bb45f3de296de3ce00b1275eb34c25 # v3.3.1
)
FetchContent_MakeAvailable(sol2)

message(STATUS "Downloading pugixml")
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG db78afc2b7d8f043b4bc6b185635d949ea2ed2a8 # v1.14
)
FetchContent_MakeAvailable(pugixml)

message(STATUS "Downloading tinyxml2")
FetchContent_Declare(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG 321ea883b7190d4e85cae5512a12e5eaa8f8731f # v10.0.0
)
FetchContent_MakeAvailable(tinyxml2)

message(STATUS "Copying data files")
file(COPY ${CMAKE_SOURCE_DIR}/test/data/translations DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

SET(
    I18N_TEST_SOURCES
    core/api.cpp
    core/registry.cpp
    util/split_iterator.cpp
    util/file.cpp
    translators/basic.cpp
    translators/nlohmann_json.cpp
    translators/rapidjson.cpp
    translators/sol2.cpp
    translators/pugixml.cpp
    translators/tinyxml2.cpp
)

include_directories(${RAPIDJSON_INCLUDE_DIRS} ${LUA_INCLUDE_DIRS})

add_executable(i18n_tests ${I18N_TEST_SOURCES})

target_link_libraries(
    i18n_tests
    PRIVATE
    i18n::i18n
    nlohmann_json::nlohmann_json
    Catch2::Catch2WithMain
    RapidJSON
    lua::lua
    sol2::sol2
    pugixml::pugixml
    tinyxml2::tinyxml2
)

add_test(NAME i18n_tests COMMAND i18n_tests)
