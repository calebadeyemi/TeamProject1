# Team Project 1: Database

## Testing

Adding a test is fairly simple. Create a new cpp file under the 
`tests/unit_tests` directory. Test files should be named something like 
`objectTests.cpp`.

Assure the `tests/unit_tests/CmakeLists.txt` file entry is updated for the file:

``` cpp 
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Unit_Tests_run
    test_example.cpp
)

target_link_libraries(Unit_Tests_run gtest gtest_main)
target_link_libraries(Unit_Tests_run ${CMAKE_PROJECT_NAME}_lib)
```

In the test file, start with this template:

``` cpp 
#include "gtest/gtest.h"
#include "NameOfObject.h"

TEST(NameOfObjectTests, attributeBeingTested) {
    // build object here to match situation
    
    ASSERT_EQ(expected, Object.Method(params));
}
```

There are different assertions to test. You can do 99% of testing with 
`ASSERT_EQ(expected, actual)`, `ASSERT_TRUE(value)` and `ASSERT_FALSE(value)`.
When comparing values it is best to use `ASSERT_EQ` because the message is
more verbose.
