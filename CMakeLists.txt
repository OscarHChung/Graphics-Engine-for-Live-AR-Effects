cmake_minimum_required(VERSION 3.10)
project(SnapShaderPluginEngine)

set(CMAKE_CXX_STANDARD 17)

# Add GLAD library
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# Main executable
add_executable(SnapShaderPluginEngine
    src/main.cpp
    src/Engine.cpp
    src/Shader.cpp
    src/Plugin.cpp
    src/Metrics.cpp
)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
target_include_directories(SnapShaderPluginEngine PRIVATE include)

# Link libraries
target_link_libraries(SnapShaderPluginEngine 
    glfw 
    OpenGL::GL 
    glad
)