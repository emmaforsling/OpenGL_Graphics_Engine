#version 330 core

// Input 
layout(location = 0) in vec3 vertexPos_ws;
layout(location = 1) in vec2 uvCoordinates;
layout(location = 2) in vec3 vertexNormal_ws;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

out vec3 normal;
out vec2 uv;

void main() {
	gl_Position = MVP * vec4(vertexPos_ws, 1.0);
	uv = uvCoordinates;
	normal = vec3(transpose(inverse(V * M)) * vec4(vertexNormal_ws, 1.0));
}