#pragma once
#include <chrono>
#include <vector>
#include <fstream>

class Metrics {
public:
    Metrics();
    ~Metrics();
    
    void beginFrame();
    void endFrame();
    double getLastFrameTime() const { return lastFrameTime; }
    double getAverageFPS() const;
    void saveToFile(const char* filename);

private:
    std::chrono::high_resolution_clock::time_point frameStart;
    double lastFrameTime;
    std::vector<double> frameTimes;
    std::ofstream logFile;
    int frameCount;
    
    static constexpr int MAX_SAMPLES = 1000;
};