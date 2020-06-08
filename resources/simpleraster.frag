#version 450

vec3 SkyColour = vec3(186.0f / 255.0f, 214.0f / 255.0f, 254.0f / 255.0f);

in vec3 fTexCoord;
in float fZ;
in float fW;

out vec4 oColour;

float near = 0.1;
float far = 1000;

void main() {

	float depth = fZ / fW;

	float ndc = depth * 2.0 - 1.0;
	float linear = (2.0 * near * far) / (far + near - ndc * (far - near));

	oColour = vec4(linear, linear, linear, 1);

}
