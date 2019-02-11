project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        Table.h
        Database.h
        )

set(SOURCE_FILES
        Table.cpp Database.cpp)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
