#pragma once
#include <string>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void reloadFragment(const char* fragmentPath);

private:
    std::string vertexPath;  // Store for potential reloading
};