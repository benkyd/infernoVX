#version 450

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vTexCoord;

out vec3 fTexCoord;

void main()
{
    fTexCoord = vTexCoord;
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0, 1.0); 
}  
