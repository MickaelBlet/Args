if(BUILD_COVERAGE)
    set(FIXTURES_COVERAGE_LIST)
endif()

file(GLOB test_files "*.cpp")

foreach(file ${test_files})
    get_filename_component(filenamewe ${file} NAME_WE)
    add_executable("${filenamewe}.gtest" ${file})
    set_target_properties("${filenamewe}.gtest" PROPERTIES
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include;${CMAKE_CURRENT_SOURCE_DIR}/include"
        LINK_LIBRARIES "gmock_main;gmock;pthread;${PROJECT_NAME}"
    )
    add_test(NAME "${filenamewe}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.gtest>")
    if(BUILD_COVERAGE)
        set_property(TEST "${filenamewe}.gtest" PROPERTY FIXTURES_SETUP "${filenamewe}.gtest.fixture")
        list(APPEND FIXTURES_COVERAGE_LIST "${filenamewe}.gtest.fixture")
    endif()
endforeach()

if(BUILD_COVERAGE)
    file(GLOB src_files "../src/*.cpp")
    foreach(file ${src_files})
        get_filename_component(filenamewe ${file} NAME_WE)
        add_test(NAME "${filenamewe}.gcov" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"${filenamewe}.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"${filenamewe}.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
        set_property(TEST "${filenamewe}.gcov" PROPERTY FIXTURES_REQUIRED ${FIXTURES_COVERAGE_LIST})
        set_property(TEST "${filenamewe}.gcov" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
    endforeach()
endif()