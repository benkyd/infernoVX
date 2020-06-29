#version 450 

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vTexCoord;

out vec3 fColour;
out vec3 fTexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

void main() {
	
	fTexCoord = vTexCoord;
	
	gl_Position = Proj * View * Model * vec4(vPosition, 1.0);

	fColour = gl_Position.rgb;
}
