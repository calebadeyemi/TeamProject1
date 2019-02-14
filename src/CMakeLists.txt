project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        Database.h
        Table.h
        Record.h
        )

set(IMPLEMENTATION_FILES
        Table.cpp
        Database.cpp
        Record.cpp
        )

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${IMPLEMENTATION_FILES}
        ${HEADER_FILES}
        )
