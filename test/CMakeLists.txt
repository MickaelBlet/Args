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
    add_test(NAME "gcov_argparsor-argparsor.cpp" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"argparsor-argparsor.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"argparsor-argparsor.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
    add_test(NAME "gcov_argparsor-argument.cpp" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"argparsor-argument.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"argparsor-argument.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
    add_test(NAME "gcov_argparsor-valid.cpp" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"argparsor-valid.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"argparsor-valid.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
    set_property(TEST "gcov_argparsor-argparsor.cpp" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
    set_property(TEST "gcov_argparsor-argument.cpp" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
    set_property(TEST "gcov_argparsor-valid.cpp" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
endif() # BUILD_COVERAGE