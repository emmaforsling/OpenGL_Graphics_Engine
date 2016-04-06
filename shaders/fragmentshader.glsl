#version 330 core

in vec3 normal;
in vec2 uv;

uniform sampler2D myTextureSampler;

out vec4 fragmentColor;

vec3 lightDirection = normalize(vec3(-1.0, -1.0, -1.0));

void main() {
	
	float diffuseLighting = max(0.0, dot(normal, -lightDirection));
    //fragmentColor = diffuseLighting * vec4(1.0,1.0,1.0,1.0);
    fragmentColor = diffuseLighting * texture( myTextureSampler, uv );
}
