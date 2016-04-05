#version 330 core

in vec3 normal;
in vec2 uv;

uniform sampler2D myTextureSampler;

out vec4 fragmentColor;

void main() {
	fragmentColor = texture( myTextureSampler, uv );
    //fragmentColor = vec4(1.0,0.0,0.0,1.0);
}