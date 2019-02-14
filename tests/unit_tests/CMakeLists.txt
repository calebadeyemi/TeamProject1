include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_NAME tests)

add_executable(${TEST_NAME}
    test_example.cpp
        )

set_target_properties(gtest gtest_main ${TEST_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/bin"
        )

target_link_libraries(${TEST_NAME} gtest gtest_main)

target_link_libraries(${TEST_NAME}
 ${CMAKE_PROJECT_NAME}_lib)