#pragma once
#include <string>
#include "Shader.hpp"

class Plugin {
public:
    Plugin(const char* fragmentPath);
    void inject(Shader& shader);

private:
    std::string fragmentPath;
};
