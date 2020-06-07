#version 450 

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vTexCoord;

out vec3 fTexCoord;
out float fDistance;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;

void main() {
	
	fTexCoord = vTexCoord;
	
	// Makes no sense but it works
	fDistance = (
		gl_Position.x * gl_Position.x + 
		gl_Position.y * gl_Position.y + 
		gl_Position.z * gl_Position.z
	);

	gl_Position = Proj * View * Model * vec4(vPosition, 1.0);

}
