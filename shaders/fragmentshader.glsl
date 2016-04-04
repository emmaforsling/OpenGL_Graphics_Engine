#version 330 core

in vec3 normal;
in vec2 uv;

out vec4 fragmentColor;

void main() {
    fragmentColor.rgb = vec4(1.0,0.0,0.0,1.0);
}