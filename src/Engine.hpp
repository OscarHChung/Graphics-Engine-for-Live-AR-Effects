#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <chrono>
#include "Shader.hpp"
#include "Plugin.hpp"
#include "Metrics.hpp"

class Engine {
public:
    Engine(int w, int h, const std::string& title);
    ~Engine();
    void run();
    
    // Get current FPS
    double getFPS() const { return currentFPS; }
    
    // Measure shader swap time
    double measureShaderSwapTime(const char* fragmentPath);

private:
    void init();
    void render();
    void loadShaders();
    void setupGeometry();
    void updateFPS();

    int width, height;
    GLFWwindow* window;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Plugin> plugin;
    Metrics metrics;
    
    // Geometry (full-screen quad for effects)
    unsigned int VAO, VBO;
    
    // FPS tracking
    double currentFPS;
    std::chrono::high_resolution_clock::time_point lastFPSUpdate;
    int frameCount;
    
    // VSync control for high FPS
    bool vsyncEnabled;
};