#version 330 core

in vec3 normal_ws;
in vec3 fragPos_ws;
in vec2 uv;

uniform sampler2D myTextureSampler;
uniform vec3 cameraPos_ws;

out vec4 fragmentColor;

//vec3 lightDirection = normalize(vec3(-1.0, -1.0, -1.0));
vec3 lightPosition_ws = vec3(0.0, 0.0, 10.0);

void main() {

	// View direction
	vec3 viewDir_ws = normalize(fragPos_ws - cameraPos_ws);

	// Light direction
	vec3 lightDirection_ws = normalize(lightPosition_ws - fragPos_ws);

	// Phong shading

	// Coefficients
	float k_diff = 0.5;
	float k_spec = 0.5;

	// Diffuse light
	float diffuseLighting = max(0.0, dot(normal_ws, lightDirection_ws));

	// Specular light
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
	float specularPower = 20.0;
	vec3 reflectionDir_ws = reflect(lightDirection_ws, normal_ws);
	float specularLight = pow(max(0.0, dot(reflectionDir_ws, viewDir_ws)), specularPower);

	// Composite lighting contributions

    fragmentColor = k_diff * diffuseLighting * texture( myTextureSampler, uv ) + k_spec * specularLight * specularColor;
}
