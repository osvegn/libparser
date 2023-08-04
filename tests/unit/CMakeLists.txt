set(SOURCES_ROOT ${PROJECT_SOURCE_DIR}/tests/unit)
set(INCLUDES_ROOT ${PROJECT_SOURCE_DIR}/includes)

set(TEST_NAME test_parser)
set(TEST_SOURCES
    ${SOURCES_ROOT}/test_parser.c
)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} parser criterion)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDES_ROOT})

add_test(${TEST_NAME} ${TEST_NAME})

set_target_properties(${TEST_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
