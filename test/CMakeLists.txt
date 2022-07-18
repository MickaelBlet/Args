include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB test_files "*.cpp")

foreach(file ${test_files})
    get_filename_component(filenamewe ${file} NAME_WE)
    add_executable("${filenamewe}.gtest" ${file})
    set_target_properties("${filenamewe}.gtest"
        PROPERTIES
            CXX_STANDARD "${CMAKE_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
    )
    target_compile_options("${filenamewe}.gtest" PRIVATE -Wall -Wextra -Werror)
    target_link_libraries("${filenamewe}.gtest" gtest_main gtest pthread)
    target_link_libraries("${filenamewe}.gtest" argparsor)
    add_test(NAME "${filenamewe}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.gtest>")
endforeach()

if (BUILD_COVERAGE)
    add_test(NAME "gcov_argparsor.cpp" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"argparsor.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"argparsor.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
    set_property(TEST "gcov_argparsor.cpp" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
endif() # BUILD_COVERAGE