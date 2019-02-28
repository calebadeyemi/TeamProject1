cmake_minimum_required(VERSION 3.9)
project(database)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME}_run main.cpp)

set_target_properties(${CMAKE_PROJECT_NAME}_run
        PROPERTIES
        FRAMEWORK ON
        PUBLIC_HEADER src/*.h
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

include_directories(src)

set(PUBLIC_HEADERS GLOB src/*.h)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)
