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
)

include_directories(${RAPIDJSON_INCLUDE_DIRS})

add_executable(i18n_tests ${I18N_TEST_SOURCES})

target_link_libraries(
    i18n_tests
    PRIVATE
    i18n::i18n
    nlohmann_json::nlohmann_json
    Catch2::Catch2WithMain
    RapidJSON
)

add_test(NAME i18n_tests COMMAND i18n_tests)
