cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(learn-gl VERSION 0.1.0 LANGUAGES CXX C)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third-party/glfw3")
find_package(glfw3 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/chapter1)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter2)