include_directories(${gtest_SOURCE_DIR}/include)
set(TEST_NAME tests)

add_executable(${TEST_NAME}
    test_example.cpp
        DatabaseTests.cpp TableTests.cpp QueryParserTests.cpp)

target_link_libraries(${TEST_NAME} gtest gtest_main)

target_link_libraries(${TEST_NAME}
 ${CMAKE_PROJECT_NAME}_lib)