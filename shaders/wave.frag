#version 330 core

in vec2 TexCoord;
in vec2 FragCoord;

out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    // Apply wave distortion
    vec2 uv = FragCoord;
    uv.x += sin(uv.y * 10.0 + u_time * 2.0) * 0.05;
    uv.y += cos(uv.x * 10.0 + u_time * 2.0) * 0.05;
    
    float r = 0.5 + 0.5 * sin(u_time + uv.x * 3.0);
    float g = 0.5 + 0.5 * cos(u_time + uv.y * 3.0);
    float b = 0.5 + 0.5 * sin(u_time * 0.5 + length(uv) * 5.0);
    
    FragColor = vec4(r, g, b, 1.0);
}