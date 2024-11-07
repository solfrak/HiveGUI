cmake_minimum_required(VERSION 3.29)
project(HiveGUI)

set(CMAKE_CXX_STANDARD 20)

add_library(HiveGUI STATIC src/hivegui.cpp include/hivegui.h include/UIprimitive.h)
target_include_directories(HiveGUI PRIVATE include)

# Test
add_subdirectory(test)

# Demo
add_subdirectory(demo)