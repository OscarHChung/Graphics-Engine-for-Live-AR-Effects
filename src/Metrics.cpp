#include "Metrics.hpp"
#include <numeric>
#include <algorithm>
#include <iostream>

Metrics::Metrics() : lastFrameTime(0.0), frameCount(0) {
    frameTimes.reserve(MAX_SAMPLES);
}

Metrics::~Metrics() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Metrics::beginFrame() {
    frameStart = std::chrono::high_resolution_clock::now();
}

void Metrics::endFrame() {
    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        frameEnd - frameStart
    ).count();
    
    lastFrameTime = duration / 1000.0; // Convert to milliseconds
    
    // Keep rolling window of frame times
    if (frameTimes.size() >= MAX_SAMPLES) {
        frameTimes.erase(frameTimes.begin());
    }
    frameTimes.push_back(lastFrameTime);
    
    frameCount++;
}

double Metrics::getAverageFPS() const {
    if (frameTimes.empty()) return 0.0;
    
    double avgFrameTime = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / frameTimes.size();
    return 1000.0 / avgFrameTime; // Convert ms to FPS
}

void Metrics::saveToFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open metrics file: " << filename << std::endl;
        return;
    }
    
    file << "=== Performance Metrics ===" << std::endl;
    file << "Total Frames: " << frameCount << std::endl;
    file << "Average FPS: " << getAverageFPS() << std::endl;
    
    if (!frameTimes.empty()) {
        double avgFrameTime = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / frameTimes.size();
        double minFrameTime = *std::min_element(frameTimes.begin(), frameTimes.end());
        double maxFrameTime = *std::max_element(frameTimes.begin(), frameTimes.end());
        
        file << "Average Frame Time: " << avgFrameTime << " ms" << std::endl;
        file << "Min Frame Time: " << minFrameTime << " ms" << std::endl;
        file << "Max Frame Time: " << maxFrameTime << " ms" << std::endl;
        file << "Max FPS: " << (1000.0 / minFrameTime) << std::endl;
    }
    
    file << "\n=== Recent Frame Times ===" << std::endl;
    for (size_t i = 0; i < frameTimes.size() && i < 100; ++i) {
        file << "Frame " << i << ": " << frameTimes[i] << " ms" << std::endl;
    }
    
    file.close();
    std::cout << "Metrics saved to " << filename << std::endl;
}