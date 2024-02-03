cmake_minimum_required(VERSION 3.19)

project(i18n_tests CXX)

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

message(STATUS "Copying data files")
file(COPY ${CMAKE_SOURCE_DIR}/test/data/translations DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/test/data/dummy.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

SET(
    I18N_TEST_SOURCES
    i18n.cpp
    registry.cpp
    split_iterator.cpp
    utils.cpp
    translators/basic.cpp
    translators/nlohmann_json.cpp
)

add_executable(i18n_tests ${I18N_TEST_SOURCES})

target_link_libraries(
    i18n_tests
    PRIVATE
    i18n::i18n
    nlohmann_json::nlohmann_json
    Catch2::Catch2WithMain
)

