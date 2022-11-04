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
    target_compile_options("${filenamewe}.gtest" PRIVATE -pedantic -Wall -Wextra -Werror)
    target_link_libraries("${filenamewe}.gtest" gmock_main gmock pthread)
    target_link_libraries("${filenamewe}.gtest" argparsor)
    add_test(NAME "${filenamewe}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.gtest>")
endforeach()


if (BUILD_COVERAGE)
    file(GLOB src_files "../src/*.cpp")
    foreach(file ${src_files})
        get_filename_component(filenamewe ${file} NAME_WE)
        message("find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"${filenamewe}.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"${filenamewe}.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
        add_test(NAME "gcov_${filenamewe}" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"${filenamewe}.cpp.gcda\" -exec sh -c \"gcov -n \\\"{}\\\" | grep -A 1 \\\"${filenamewe}.cpp\\\" | grep \\\":\\\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'\" \\;")
        set_property(TEST "gcov_${filenamewe}" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
    endforeach()
endif() # BUILD_COVERAGE