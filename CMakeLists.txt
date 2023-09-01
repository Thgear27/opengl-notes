cmake_minimum_required(VERSION 3.10)

project(Openglnotes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(Openglnotes
              src/glad.c
              src/main.cpp)

target_include_directories(Openglnotes PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(Openglnotes glfw)