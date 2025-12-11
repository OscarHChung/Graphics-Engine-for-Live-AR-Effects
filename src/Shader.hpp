#pragma once
#include <string>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void reloadFragment(const char* fragmentPath);
    
    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;

private:
    std::string vertexPath;
    unsigned int compileShader(const char* shaderCode, unsigned int shaderType);
    void checkCompileErrors(unsigned int shader, const std::string& type);
};