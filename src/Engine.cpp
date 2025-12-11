#include "Engine.hpp"
#include <iostream>
#include <vector>

Engine::Engine(int w, int h, const std::string& title)
    : width(w), height(h), window(nullptr), 
      currentFPS(0.0), frameCount(0), vsyncEnabled(false) {
    init();
    glfwSetWindowTitle(window, title.c_str());
    setupGeometry();
    loadShaders();
    lastFPSUpdate = std::chrono::high_resolution_clock::now();
}

Engine::~Engine() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
    
    // Disable VSync for maximum FPS
    glfwSwapInterval(0);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    
    std::cout << "OpenGL initialized successfully" << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "VSync: " << (vsyncEnabled ? "ON" : "OFF (max FPS mode)") << std::endl;
}

void Engine::setupGeometry() {
    // Full-screen quad (2 triangles)
    float vertices[] = {
        // positions        // texture coords
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Engine::loadShaders() {
    shader = std::make_unique<Shader>("shaders/base.vert", "shaders/base.frag");
    plugin = std::make_unique<Plugin>("shaders/invert.frag");
    std::cout << "Shaders loaded successfully" << std::endl;
}

void Engine::updateFPS() {
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        currentTime - lastFPSUpdate
    ).count();
    
    // Update FPS every 500ms
    if (duration >= 500) {
        currentFPS = (frameCount * 1000.0) / duration;
        
        // Update window title with FPS
        std::string title = "Snap Shader Engine - " + 
                          std::to_string(static_cast<int>(currentFPS)) + " FPS";
        glfwSetWindowTitle(window, title.c_str());
        
        frameCount = 0;
        lastFPSUpdate = currentTime;
    }
}

void Engine::render() {
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    
    // Set uniforms for visual effects
    float time = static_cast<float>(glfwGetTime());
    shader->setFloat("u_time", time);
    shader->setVec2("u_resolution", static_cast<float>(width), static_cast<float>(height));
    
    // Apply plugin effect
    plugin->inject(*shader);
    
    // Draw full-screen quad
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Engine::run() {
    std::cout << "\n=== Starting Render Loop ===" << std::endl;
    std::cout << "Press ESC to exit" << std::endl;
    std::cout << "Press SPACE to toggle effect" << std::endl;
    
    bool effectToggle = false;
    
    while (!glfwWindowShouldClose(window)) {
        metrics.beginFrame();
        
        // Handle input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Toggle effect with spacebar
        static bool spacePressed = false;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
            spacePressed = true;
            effectToggle = !effectToggle;
            
            auto start = std::chrono::high_resolution_clock::now();
            if (effectToggle) {
                plugin = std::make_unique<Plugin>("shaders/wave.frag");
            } else {
                plugin = std::make_unique<Plugin>("shaders/invert.frag");
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto swapTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
            
            std::cout << "Effect swap time: " << swapTime << " ms" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            spacePressed = false;
        }
        
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        metrics.endFrame();
        updateFPS();
    }
    
    std::cout << "\n=== Performance Summary ===" << std::endl;
    std::cout << "Average FPS: " << currentFPS << std::endl;
    std::cout << "Final frame time: " << metrics.getLastFrameTime() << " ms" << std::endl;
}

double Engine::measureShaderSwapTime(const char* fragmentPath) {
    auto start = std::chrono::high_resolution_clock::now();
    plugin = std::make_unique<Plugin>(fragmentPath);
    auto end = std::chrono::high_resolution_clock::now();
    
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
}