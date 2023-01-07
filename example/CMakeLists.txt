file(GLOB example_files "*.cpp")

foreach(file ${example_files})
    get_filename_component(filenamewe ${file} NAME_WE)
    add_executable("${filenamewe}.example" ${file})
    set_target_properties("${filenamewe}.example"
        PROPERTIES
            CXX_STANDARD "${CMAKE_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
            COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
            INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../include;${CMAKE_CURRENT_SOURCE_DIR}/include"
            LINK_LIBRARIES "${PROJECT_NAME}"
    )
endforeach()