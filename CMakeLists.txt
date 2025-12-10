cmake_minimum_required(VERSION 3.10)
project(SnapShaderPluginEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(SnapShaderPluginEngine
    src/main.cpp
    src/Engine.cpp
    src/Shader.cpp
    src/Plugin.cpp
    src/Metrics.cpp
)

find_package(OpenGL REQUIRED)

add_subdirectory(glfw)
include_directories(glfw/include)

target_link_libraries(SnapShaderPluginEngine glfw OpenGL::GL)
