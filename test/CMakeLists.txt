set(library_project_name "${PROJECT_NAME}")

get_target_property(library_include_dirs "${library_project_name}" INTERFACE_INCLUDE_DIRECTORIES)

set(test_source_files
    "${CMAKE_CURRENT_SOURCE_DIR}/array.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/boolean.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/common.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/dict.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/null.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/number.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/object.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/string.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/union.cpp"
)

if(BUILD_COVERAGE)
    set(FIXTURES_COVERAGE_LIST)
endif()

foreach(file ${test_source_files})
    get_filename_component(filenamewe "${file}" NAME_WE)
    add_executable("${filenamewe}.${library_project_name}.gtest" "${file}")
    set_target_properties("${filenamewe}.${library_project_name}.gtest" PROPERTIES
        CXX_STANDARD "${CMAKE_CXX_STANDARD}"
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        NO_SYSTEM_FROM_IMPORTED ON
        COMPILE_FLAGS "-pedantic -Wall -Wextra -Werror"
        INCLUDE_DIRECTORIES "${library_include_dirs};${CMAKE_CURRENT_SOURCE_DIR}/include"
        LINK_LIBRARIES "gmock_main;gmock;gtest;pthread;${library_project_name}"
    )
    target_compile_options("${filenamewe}.${library_project_name}.gtest" PRIVATE -g -O0 --coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline)
    target_link_libraries("${filenamewe}.${library_project_name}.gtest" gcov)
    add_test(NAME "${filenamewe}.${library_project_name}.gtest" COMMAND "$<TARGET_FILE:${filenamewe}.${library_project_name}.gtest>")
    if(BUILD_COVERAGE)
        set_property(TEST "${filenamewe}.${library_project_name}.gtest" PROPERTY FIXTURES_SETUP "${filenamewe}.${library_project_name}.gtest.fixture")
        list(APPEND FIXTURES_COVERAGE_LIST "${filenamewe}.${library_project_name}.gtest.fixture")
    endif()
endforeach()

if(BUILD_COVERAGE)
    add_test(NAME "dict.gcov" COMMAND sh -c "find \"${CMAKE_CURRENT_BINARY_DIR}/..\" -name \"*.cpp.gcda\" | xargs gcov -n | grep -A 1 \"dict.h\" | grep \":\" | sed 's/[^:]\\+[:]\\([0-9]\\+[.][0-9]\\+%\\).*/\\1/g'")
    set_property(TEST "dict.gcov" PROPERTY LABELS noMemcheck)
    set_property(TEST "dict.gcov" PROPERTY FIXTURES_REQUIRED ${FIXTURES_COVERAGE_LIST})
    set_property(TEST "dict.gcov" PROPERTY PASS_REGULAR_EXPRESSION "^100.00%")
endif()

find_program(VALGRIND "valgrind")
if (VALGRIND AND NOT TARGET "valgrind")
    set(DART_CONFIG DartConfiguration.tcl)
    add_custom_target("${DART_CONFIG}"
        COMMAND echo "MemoryCheckCommand: ${VALGRIND}" >> "${DART_CONFIG}"
        COMMENT "Generating ${DART_CONFIG}"
    )
    set(VALGRIND_ARGS
        --leak-check=full
        --error-exitcode=255
    )
    set(LOGFILE memcheck.log)
    add_custom_target("valgrind"
        COMMAND ${CMAKE_CTEST_COMMAND} -O ${LOGFILE} -D ExperimentalMemCheck --overwrite MemoryCheckCommandOptions="${VALGRIND_ARGS}" -j 16 -T memcheck -LE "^noMemcheck$"
        COMMAND tail -n1 ${LOGFILE} | grep 'Memory checking results:' > /dev/null
        COMMAND rm -f ${LOGFILE}
        DEPENDS ${DART_CONFIG}
    )
endif()
