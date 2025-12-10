#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.hpp"
#include "Plugin.hpp"
#include "Metrics.hpp"

class Engine {
public:
    Engine(int w, int h, const std::string& title);
    void run();

private:
    void init();
    void render();

    int width, height;
    GLFWwindow* window;

    Shader shader;
    Plugin plugin;
    Metrics metrics;
};
