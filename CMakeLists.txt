cmake_minimum_required(VERSION 3.18)

project(circles)

find_package(raylib REQUIRED)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    circles
    src/main.cpp
    src/app.cpp
    src/math.cpp
)

target_include_directories(circles PRIVATE include/)

target_link_libraries(circles raylib)
