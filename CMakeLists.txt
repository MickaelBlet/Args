cmake_minimum_required(VERSION 3.1)

project(argparsor CXX)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library("${PROJECT_NAME}" ${SOURCES})
target_compile_options("${PROJECT_NAME}" PRIVATE -pedantic -Wall -Wextra -Werror)

set_target_properties("${PROJECT_NAME}"
    PROPERTIES
        CXX_STANDARD 98
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        PUBLIC_HEADER "include/optionator.hpp"
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)

if (BUILD_EXAMPLE)
    message(STATUS "Enable BUILD_EXAMPLE: ${BUILD_EXAMPLE}")
    add_subdirectory(example)
endif() # BUILD_EXAMPLE

if (BUILD_TESTING)
    message(STATUS "Enable BUILD_TESTING: ${BUILD_TESTING}")
    enable_testing()

    if (BUILD_COVERAGE)
        message(STATUS "Enable BUILD_COVERAGE: ${BUILD_COVERAGE}")
        target_compile_options("${PROJECT_NAME}" PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
        target_link_libraries("${PROJECT_NAME}" gcov)
        # Path to CodeCoverage
        set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/etc/cmake")
        include(CodeCoverage)
        append_coverage_compiler_flags_to_target("${PROJECT_NAME}")
    endif() # BUILD_COVERAGE

    add_subdirectory(test)
endif() # BUILD_TESTING