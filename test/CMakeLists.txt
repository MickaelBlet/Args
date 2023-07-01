set(library_project_name args)

get_target_property(library_include_dirs "${library_project_name}" INCLUDE_DIRECTORIES)

set(test_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/accessDenied.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/addArgument.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/getUsage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/getVersion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/parseArguments.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/removeArguments.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/updateArgument.cpp"
)

if(BUILD_COVERAGE)
    set(FIXTURES_COVERAGE_LIST)
endif()

foreach(file ${test_source_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.gtest" "${file}")
    set_target_properties("${filenamewe}.gtest" PROPERTIES
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${library_include_dirs};${CMAKE_CURRENT_SOURCE_DIR}/include"
        LINK_LIBRARIES "gmock_main;gtest;gmock;pthread;${library_project_name}"
    )
    add_test(NAME "${filenamewe}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.gtest>")
    if(BUILD_COVERAGE)
        set_property(TEST "${filenamewe}.gtest" PROPERTY FIXTURES_SETUP "${filenamewe}.gtest.fixture")
        list(APPEND FIXTURES_COVERAGE_LIST "${filenamewe}.gtest.fixture")
    endif()
endforeach()

if(BUILD_COVERAGE)
    get_target_property(library_source_files "${library_project_name}" SOURCES)
    foreach(file ${library_source_files})
        get_filename_component(filenamewe ${file} NAME_WE)
        add_test(NAME "${filenamewe}.gcov" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"${filenamewe}.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"${filenamewe}.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
        set_property(TEST "${filenamewe}.gcov" PROPERTY FIXTURES_REQUIRED ${FIXTURES_COVERAGE_LIST})
        set_property(TEST "${filenamewe}.gcov" PROPERTY PASS_REGULAR_EXPRESSION "^100\\.00%")
    endforeach()
endif()