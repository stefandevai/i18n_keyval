cmake_minimum_required(VERSION 3.19)

project(i18n VERSION 0.1.0 LANGUAGES CXX)

option(I18N_BUILD_TESTS "Build tests" OFF)

SET(
    I18N_SOURCES
    src/i18n/i18n.cpp
    src/i18n/registry.cpp
    src/i18n/utils.cpp
)

add_library(i18n ${I18N_SOURCES})
add_library(i18n::i18n ALIAS i18n)

target_compile_features(i18n PUBLIC cxx_std_20)

if (MSVC)
    target_compile_options(i18n PUBLIC /W4)
else()
    target_compile_options(i18n PUBLIC -Wall -Wextra -O3)
endif()

target_include_directories(i18n PUBLIC "src")

if (I18N_BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory("test")
endif()
