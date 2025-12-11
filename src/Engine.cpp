#include "Engine.hpp"
#include <iostream>

Engine::Engine(int w, int h, const std::string& title)
    : width(w), height(h), window(nullptr) {
    init();
    glfwSetWindowTitle(window, title.c_str());
    loadShaders();
}

Engine::~Engine() {
    glfwTerminate();
}

void Engine::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    
    std::cout << "OpenGL initialized successfully" << std::endl;
}

void Engine::loadShaders() {
    shader = std::make_unique<Shader>("shaders/base.vert", "shaders/base.frag");
    plugin = std::make_unique<Plugin>("shaders/invert.frag");
}

void Engine::render() {
    glClearColor(0.05f, 0.05f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    plugin->inject(*shader);
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