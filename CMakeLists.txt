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
    add_subdirectory(tests/unit)
endif()

add_library(${TARGET}_shared SHARED ${SOURCES})
add_library(${TARGET}_static STATIC ${SOURCES})

target_include_directories(${TARGET}_shared
    PUBLIC ${INCLUDES_ROOT}
)

target_include_directories(${TARGET}_static
    PUBLIC ${INCLUDES_ROOT}
)

set_target_properties(${TARGET}_shared
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

set_target_properties(${TARGET}_static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
