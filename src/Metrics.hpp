#pragma once
#include <chrono>

class Metrics {
public:
    void beginFrame();
    void endFrame();

private:
    std::chrono::high_resolution_clock::time_point start;
};
