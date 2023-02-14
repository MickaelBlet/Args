set(library_project_name argparsor)

find_program(PYTHON3 "python3")
find_program(CLANG_FORMAT "clang-format")
if(PYTHON3 AND CLANG_FORMAT)
    get_target_property(library_source_files "${library_project_name}" SOURCES)
    add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/mblet/argparsor.h"
        COMMAND ${PYTHON3} ./etc/script/amalgamate.py -c ./etc/script/config_argparsor.json -s . > /dev/null
        COMMAND ${CLANG_FORMAT} -i ./single_include/mblet/argparsor.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
        DEPENDS
            ${library_source_files}
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/action.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/argparsor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/argument.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/exception.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/usage.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/utils.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/valid.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../include/mblet/argparsor/vector.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/../etc/script/config_argparsor.json"
        COMMENT "Generating single_include/mblet/argparsor.h"
    )
    add_custom_target("${library_project_name}_single_include"
        DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/../single_include/mblet/argparsor.h"
    )
    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
    add_dependencies("${library_project_name}" "${library_project_name}_single_include")
endif()