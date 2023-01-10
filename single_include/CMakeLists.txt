find_program(PYTHON3 "python3")
find_program(CLANG_FORMAT "clang-format")
if(PYTHON3 AND CLANG_FORMAT)
    execute_process(
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        COMMAND bash -c "./etc/script/amalgamate.py -c ./etc/script/config_argparsor.json -s . && clang-format -i ./single_include/mblet/argparsor.h"
        OUTPUT_QUIET
        RESULT_VARIABLE generate_result
    )
    if(generate_result EQUAL 0)
        message(STATUS "Generate \"single_include/mblet/argparsor.h\" done")
        if(BUILD_TESTING)
            add_subdirectory(test)
        endif()
    else()
        message(FATAL_ERROR "Generate \"single_include/mblet/argparsor.h\" failed")
    endif()
endif()