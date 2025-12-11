# Graphics Engine for Live AR Effects

A high-performance C++ graphics engine with **hot-swappable shader system** for real-time visual effects, achieving **300+ FPS at 1080p** with 4ms effect transitions.

## What It Does

This engine demonstrates the core technology behind AR filter platforms like Snapchat Lenses, Instagram filters, and TikTok effects. It renders GPU-accelerated visual effects with **zero-downtime shader swapping**, enabling instant effect changes without application restart.

## Key Features

- **300+ FPS** at 1920x1080 resolution
- **4ms shader swaps**: change effects instantly without restart
- **Plugin architecture** for modular effect system
- **Real-time performance metrics** with FPS tracking
- **5 GPU-accelerated visual effects** included
- **Cross-platform**: Mac, Linux, Windows support

## Performance (on my personal hardware)

**Hardware:** Apple M2 MacBook Pro  
**Resolution:** 1920x1080
**OpenGL:** 3.3 Core Profile

| Metric | Result |
|--------|--------|
| Average FPS | **320 FPS** |
| Frame Time | **3.1 ms** |
| Shader Swap Time | **4.2 ms** |
| Effect Overhead | **<2 ms** |

## Visual Effects

Press **SPACE** to cycle through effects in real-time:

1. **Base Gradient**: Animated color gradients
2. **Color Inversion**: Real-time color manipulation
3. **Wave Distortion**: Sinusoidal spatial warping
4. **RGB Split**: Chromatic aberration
5. **Kaleidoscope**: 6-fold mirror symmetry

## Quick Start

### Prerequisites
```bash
brew install cmake glfw
git clone https://github.com/OscarHChung/Graphics-Engine-for-Live-AR-Effects.git
cd Graphics-Engine-for-Live-AR-Effects
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./SnapShaderPluginEngine
```

**Controls:** `SPACE` = toggle effects | `ESC` = exit

