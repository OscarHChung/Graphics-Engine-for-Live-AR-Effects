cmake_minimum_required(VERSION 3.10)
project(SnapShaderPluginEngine)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DGL_SILENCE_DEPRECATION)

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

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders 
     DESTINATION ${CMAKE_BINARY_DIR})

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

# Optimization flags for maximum performance
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(SnapShaderPluginEngine PRIVATE -O3 -march=native)
endif()