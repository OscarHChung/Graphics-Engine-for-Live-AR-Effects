#include "Plugin.hpp"

Plugin::Plugin(const char* fragPath) : fragmentPath(fragPath) {}

void Plugin::inject(Shader& shader) {
    shader.reloadFragment(fragmentPath.c_str());
}
