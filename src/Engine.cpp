#include "Engine.hpp"
#include <iostream>

Engine::Engine(int w, int h, const std::string& title)
    : width(w), height(h),
      shader("shaders/base.vert", "shaders/base.frag"),
      plugin("shaders/invert.frag") {
    init();
    glfwSetWindowTitle(window, title.c_str());
}

void Engine::init() {
    glfwInit();
    window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
}

void Engine::run() {
    while (!glfwWindowShouldClose(window)) {
        metrics.beginFrame();

        render();
        glfwSwapBuffers(window);
        glfwPollEvents();

        metrics.endFrame();
    }
}

void Engine::render() {
    glClearColor(0.05f, 0.05f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    plugin.inject(shader);   // AR-style effect swap
}
