set(library_project_name "${PROJECT_NAME}")

find_program(PYTHON3 "python3")
find_program(CLANG_FORMAT "clang-format")
if(PYTHON3 AND CLANG_FORMAT)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/blet/args.h"
        COMMAND ${PYTHON3} ./third/amalgamate/amalgamate.py -c ./single_include/amalgamate_config.json -s . > /dev/null
        COMMAND ${CLANG_FORMAT} -i ./single_include/blet/args.h
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        DEPENDS
            "${library_project_name}"
            "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/amalgamate_config.json"
        COMMENT "Generating single_include/blet/args.h"
    )
endif()

add_custom_target("${library_project_name}_single_include_header"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/blet/args.h"
)
add_library("${library_project_name}_single_include" INTERFACE)
set_target_properties("${library_project_name}_single_include"
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>"
)
add_dependencies("${library_project_name}_single_include" "${library_project_name}_single_include_header")
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

#install
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${library_project_name}_single_includeConfig.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${library_project_name}_single_includeTargets.cmake\")"
)

install(TARGETS "${library_project_name}_single_include" EXPORT "${library_project_name}_single_includeTargets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/blet/args.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/blet/single_include"
)
install(EXPORT "${library_project_name}_single_includeTargets"
        FILE "${library_project_name}_single_includeTargets.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${library_project_name}_single_includeConfig.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
