cmake_minimum_required(VERSION 3.9)
project(TeamDatabase)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_library(${CMAKE_PROJECT_NAME}.out STATIC ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
