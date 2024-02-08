cmake_minimum_required(VERSION 3.19)

project(i18n VERSION 0.1.0 LANGUAGES CXX)

option(I18N_BUILD_TESTS "Build tests" OFF)
option(I18N_EXCEPTIONS "If off, compile with -fno-exceptions and print i18n exception messages" ON)

SET(
    I18N_SOURCES
    src/i18n/core/api.cpp
    src/i18n/core/registry.cpp
    src/i18n/core/common.cpp
    src/i18n/util/file.cpp
)

add_library(i18n ${I18N_SOURCES})
add_library(i18n::i18n ALIAS i18n)

target_compile_features(i18n PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(i18n PUBLIC /W4)
else()
    target_compile_options(i18n PUBLIC -Wall -Wextra -O3)
endif()

if (I18N_EXCEPTIONS)
    target_compile_definitions(i18n PUBLIC I18N_EXCEPTIONS)
endif()

if (NOT I18N_EXCEPTIONS)
    target_compile_options(i18n PUBLIC -fno-exceptions)
endif()

target_include_directories(i18n PUBLIC "src")

if (I18N_BUILD_TESTS)
    include(CTest)
    enable_testing()
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory("test")
    add_test(NAME i18n_tests COMMAND i18n_tests)
endif()
