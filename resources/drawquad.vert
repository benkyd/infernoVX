#version 450

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;

out vec2 fTexCoord;

void main()
{
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0, 1.0); 
    fTexCoord = vTexCoord;
}  
