set(library_project_name args)

find_program(PYTHON3 "python3")
find_program(CLANG_FORMAT "clang-format")
if(PYTHON3 AND CLANG_FORMAT)
    get_target_property(library_source_files "${library_project_name}" SOURCES)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/blet/args.h"
        COMMAND ${PYTHON3} ./etc/script/amalgamate.py -c ./etc/script/config_args.json -s . > /dev/null
        COMMAND ${CLANG_FORMAT} -i ./single_include/blet/args.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
        DEPENDS
            ${library_source_files}
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/action.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/args.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/argument.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/exception.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/usage.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/utils.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/valid.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/blet/args/vector.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../etc/script/config_args.json"
        COMMENT "Generating single_include/blet/args.h"
    )
    add_custom_target("${library_project_name}_single_include"
        DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/blet/args.h"
    )
    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
    add_dependencies("${library_project_name}" "${library_project_name}_single_include")
endif()