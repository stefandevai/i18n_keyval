cmake_minimum_required(VERSION 3.19)

project(i18n VERSION 0.1.0 LANGUAGES C CXX)

add_library(
    i18n
    INTERFACE
    src/i18n/i18n.hpp
    src/i18n/i18n.cpp
    src/i18n/registry.hpp
    src/i18n/registry.cpp
    src/i18n/split_iterator.hpp
    src/i18n/utils.hpp
)
add_library(i18n::i18n ALIAS i18n)

target_compile_features(i18n INTERFACE cxx_std_17)

if (MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE /W4)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -O3)
endif()

target_include_directories(i18n INTERFACE "src")

add_subdirectory("lib/json")

add_executable(test src/main.cpp)
target_link_libraries(
    test
    PRIVATE
    i18n::i18n
    nlohmann_json::nlohmann_json
)
