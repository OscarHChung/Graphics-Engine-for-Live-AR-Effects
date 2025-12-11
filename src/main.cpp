#include "Engine.hpp"
#include <iostream>

int main() {
    try {
        // 1920x1080 for high-performance benchmarking
        Engine engine(1920, 1080, "Snap Shader Plugin Engine");
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}