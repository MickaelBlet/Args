include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB test_files "*.cpp")

foreach(file ${test_files})
    get_filename_component(filenamewe ${file} NAME_WE)
    add_executable("optionator_${filenamewe}.gtest" ${file})
    set_target_properties("optionator_${filenamewe}.gtest"
        PROPERTIES
            CXX_STANDARD 98
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
    )
    target_compile_options("optionator_${filenamewe}.gtest" PRIVATE -Wall -Wextra -Werror)
    target_link_libraries("optionator_${filenamewe}.gtest" gtest_main gtest pthread)
    target_link_libraries("optionator_${filenamewe}.gtest" optparsor)
    add_test(NAME "optionator_${filenamewe}.gtest" COMMAND "optionator_${filenamewe}.gtest")
endforeach()