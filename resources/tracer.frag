#version 410 core

in vec3 vResolution;

out vec4 FragColour;

void main()
{
	vec3 col = vec3(1.0, 0.5, 0.6);



	FragColour = vec4(col, 1.0);
}
