cmake_minimum_required(VERSION 3.10)

project(Openglnotes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "src/*.h" "src/*.hpp" "src/OpenGL/*.cpp" "src/OpenGL/*.hpp")


add_executable(Openglnotes ${SOURCES})

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(Openglnotes copy_resources)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(Openglnotes PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(Openglnotes glfw)

add_custom_target(run
        COMMAND Openglnotes
        DEPENDS Openglnotes
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        COMMENT "Running Openglnotes"
        VERBATIM)