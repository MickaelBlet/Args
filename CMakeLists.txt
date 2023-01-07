cmake_minimum_required(VERSION 3.5)

project(argparsor VERSION 3.1.1 LANGUAGES CXX)

# OPTIONS
option(BUILD_EXAMPLE "Build example binaries" OFF)
option(BUILD_TESTING "Build test binaries" OFF)
option(BUILD_COVERAGE "Check coverage at end of test" OFF)
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to be used")
endif()

file(GLOB SOURCE "src/*.cpp")

add_library("${PROJECT_NAME}" ${SOURCE})

set_target_properties("${PROJECT_NAME}"
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include>"
)

# config
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")"
)

# target
install(TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Targets"
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
        DESTINATION include
)
install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
        DESTINATION "lib/cmake"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "lib/cmake"
)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND BUILD_TESTING)
    enable_testing()
    if(BUILD_COVERAGE)
        target_compile_options("${PROJECT_NAME}" PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage)
        target_link_libraries("${PROJECT_NAME}" gcov)
        include("${PROJECT_SOURCE_DIR}/etc/cmake/CodeCoverage.cmake")
        append_coverage_compiler_flags_to_target("${PROJECT_NAME}")
    endif()
    add_subdirectory(test)
    add_subdirectory(single_include/test)
endif()