cmake_minimum_required(VERSION 3.19)

project(i18n_keyval VERSION 0.8.0 LANGUAGES CXX)

option(I18N_KEYVAL_BUILD_TESTS "Build tests" OFF)
option(I18N_KEYVAL_EXCEPTIONS "If off, compile with -fno-exceptions and print i18n exception messages" ON)

SET(
    I18N_KEYVAL_SOURCES
    src/i18n_keyval/core/api.cpp
    src/i18n_keyval/core/registry.cpp
    src/i18n_keyval/core/common.cpp
    src/i18n_keyval/util/file.cpp
)

add_library(i18n_keyval ${I18N_KEYVAL_SOURCES})
add_library(i18n_keyval::i18n_keyval ALIAS i18n_keyval)

target_compile_features(i18n_keyval PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(i18n_keyval PUBLIC /W4)
else()
    target_compile_options(i18n_keyval PUBLIC -Wall -Wextra -O3)
endif()

if (I18N_KEYVAL_EXCEPTIONS)
    target_compile_definitions(i18n_keyval PUBLIC I18N_EXCEPTIONS)
endif()

if (NOT I18N_KEYVAL_EXCEPTIONS)
    target_compile_options(i18n_keyval PUBLIC -fno-exceptions)
endif()

target_include_directories(i18n_keyval PUBLIC "src")

if (I18N_KEYVAL_BUILD_TESTS)
    include(CTest)
    enable_testing()
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("test")
    add_test(NAME i18n_keyval_tests COMMAND i18n_keyval_tests)
endif()
