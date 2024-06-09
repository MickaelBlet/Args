cmake_minimum_required(VERSION 3.5)

project(blet_args VERSION 5.0.2 LANGUAGES CXX)

# OPTIONS
option(BUILD_EXAMPLE "Build example binaries" OFF)
option(BUILD_SINGLE_INCLUDE "Build single_include header" OFF)
option(BUILD_TESTING "Build test binaries" OFF)
option(BUILD_COVERAGE "Check coverage at end of test" OFF)
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to be used")
endif()
if(NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib CACHE STRING "Install destination library directory")
endif()
if(NOT CMAKE_INSTALL_BINDIR)
    set(CMAKE_INSTALL_BINDIR bin CACHE STRING "Install destination binary directory")
endif()
if(NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include CACHE STRING "Install destination include directory")
endif()

add_library("${PROJECT_NAME}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/args.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/argument.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/usage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/valid.cpp"
)

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
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include>"
)

# install
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")"
)

install(TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Targets"
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION include
)
install(EXPORT "${PROJECT_NAME}Targets"
        NAMESPACE blet::
        FILE "${PROJECT_NAME}Targets.cmake"
        DESTINATION "lib/cmake"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "lib/cmake"
)

if(BUILD_TESTING)
    enable_testing()
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(BUILD_SINGLE_INCLUDE)
    add_subdirectory(single_include)
endif()

# test
get_target_property(library_type "${PROJECT_NAME}" TYPE)
if(library_type STREQUAL "STATIC_LIBRARY" AND
   CMAKE_BUILD_TYPE STREQUAL "Debug" AND
   BUILD_TESTING)
    if(BUILD_COVERAGE)
        target_compile_options("${PROJECT_NAME}" PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors)
        target_link_libraries("${PROJECT_NAME}" gcov)
    endif()
    add_subdirectory(test)
endif()
