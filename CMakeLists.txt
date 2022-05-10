cmake_minimum_required(VERSION 2.6)

project(optionator CXX)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library("${PROJECT_NAME}" ${SOURCES})
target_compile_options("${PROJECT_NAME}" PRIVATE -Wall -Wextra -Werror -ggdb)
target_compile_definitions("${PROJECT_NAME}" PUBLIC DEBUG_LOG)

set_target_properties("${PROJECT_NAME}"
    PROPERTIES
        CXX_STANDARD 98
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        PUBLIC_HEADER "include/optionator.hpp"
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)

add_subdirectory(example)

if(BUILD_TESTING)
    message(STATUS "Enable BUILD_TESTING: ${BUILD_TESTING}")
    enable_testing()
    add_subdirectory(test)
endif()