#include "Metrics.hpp"
#include <iostream>

void Metrics::beginFrame() {
    start = std::chrono::high_resolution_clock::now();
}

void Metrics::endFrame() {
    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Frame Time: " << ms << " ms\n";
}
