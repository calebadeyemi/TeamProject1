cmake_minimum_required(VERSION 3.9)
project(TeamDatabase)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
add_library(${CMAKE_PROJECT_NAME}.out ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)
