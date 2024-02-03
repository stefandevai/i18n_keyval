cmake_minimum_required(VERSION 3.19)

project(i18n_tests CXX)

find_package(Catch2 3 QUIET)

if(Catch2_FOUND)
    message(STATUS "Using packaged catch2")
else()
    message(STATUS "Downloading catch2")
    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 05e10dfccc28c7f973727c54f850237d07d5e10f # v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/test/data/translations DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/test/data/dummy.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(i18n_tests i18n.cpp registry.cpp split_iterator.cpp utils.cpp translators/basic.cpp translators/nlohmann_json.cpp)

target_link_libraries(
    i18n_tests
    PRIVATE
    i18n::i18n
    nlohmann_json::nlohmann_json
    Catch2::Catch2WithMain
)

