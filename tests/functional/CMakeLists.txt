set(SOURCES_ROOT ${PROJECT_SOURCE_DIR}/tests/functional)
set(INCLUDES_ROOT ${PROJECT_SOURCE_DIR}/includes)

set(TEST_NAME functional_test_parser)
set(TEST_SOURCES

)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} parser)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDES_ROOT})

add_test(${TEST_NAME} ${TEST_NAME})

set_target_properties(${TEST_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
