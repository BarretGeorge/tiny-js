cmake_minimum_required(VERSION 4.1)
project(tiny_js)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/native/*.cpp")

add_executable(tiny_js main.cpp ${SOURCES})

add_subdirectory(tests)

# 设置二进制文件输出目录
set_target_properties(tiny_js PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/scripts)
