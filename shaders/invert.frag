#version 330 core

in vec2 TexCoord;
in vec2 FragCoord;

out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    // Base gradient
    vec2 uv = FragCoord;
    
    float r = 0.5 + 0.5 * sin(u_time + uv.x * 3.0);
    float g = 0.5 + 0.5 * cos(u_time + uv.y * 3.0);
    float b = 0.5 + 0.5 * sin(u_time * 0.5 + length(uv) * 5.0);
    
    vec3 color = vec3(r, g, b);
    
    // Invert the colors
    color = 1.0 - color;
    
    FragColor = vec4(color, 1.0);
}