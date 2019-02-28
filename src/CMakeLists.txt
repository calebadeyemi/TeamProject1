cmake_minimum_required(VERSION 3.9)
include(GenerateExportHeader)

project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
        Database.h
        Table.h
        Record.h
        DbError.h
        )

set(IMPLEMENTATION_FILES
        Table.cpp
        Database.cpp
        Record.cpp
        DbError.cpp
        )

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${HEADER_FILES}
        ${IMPLEMENTATION_FILES}
        )

set_target_properties(${CMAKE_PROJECT_NAME}_lib
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
