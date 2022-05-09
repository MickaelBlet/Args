cmake_minimum_required(VERSION 2.6)

project(example CXX)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB SRC "*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 98
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -ggdb)
target_link_libraries(${PROJECT_NAME} optionator)