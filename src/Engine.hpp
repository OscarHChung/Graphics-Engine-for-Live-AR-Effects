#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include "Shader.hpp"
#include "Plugin.hpp"
#include "Metrics.hpp"

class Engine {
public:
    Engine(int w, int h, const std::string& title);
    ~Engine();
    void run();

private:
    void init();
    void render();
    void loadShaders();

    int width, height;
    GLFWwindow* window;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Plugin> plugin;
    Metrics metrics;
};