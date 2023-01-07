file(GLOB test_files "*.cpp")

add_executable("already_include.single_include_test" ${test_files})

set_target_properties("already_include.single_include_test"
    PROPERTIES
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/.."
)