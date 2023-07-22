cmake_minimum_required(VERSION 3.17)

project(libparser LANGUAGES C)

set(TARGET parser)

set(SOURCES_ROOT ${PROJECT_SOURCE_DIR}/sources)
set(INCLUDES_ROOT ${PROJECT_SOURCE_DIR}/includes)

set(SOURCES
    ${SOURCES_ROOT}/parser.c
)

option(TESTING OFF)
if (TESTING)
    enable_testing()
    add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_subdirectory(tests)
endif()

add_library(${TARGET} SHARED ${SOURCES})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDES_ROOT}
)

set_target_properties(${TARGET}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
