set(library_project_name "${PROJECT_NAME}")

set(example_files
    "${CMAKE_CURRENT_SOURCE_DIR}/allType.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/append1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/append3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/argument1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/argument3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/custom-valid-transform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/default-valid.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/default-value.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/extend1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/extend3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/help.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/infinite-argument.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/infinite-number-argument.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/infinite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/none1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/none3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/quickstart.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/storeFalse.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/storeTrue.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/usageWidth.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp"
)

foreach(file ${example_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.${library_project_name}.example" "${file}")
    set_target_properties("${filenamewe}.${library_project_name}.example"
        PROPERTIES
            CXX_STANDARD "${CMAKE_CXX_STANDARD}"
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
            NO_SYSTEM_FROM_IMPORTED ON
            COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
    )
    target_link_libraries("${filenamewe}.${library_project_name}.example" PUBLIC "${library_project_name}")
endforeach()