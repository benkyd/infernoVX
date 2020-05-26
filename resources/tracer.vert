#version 410 core

layout (location = 0) in vec3 vPos;

uniform vec3 vResolution;

out vec3 iResolution;

void main()
{
    gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);


    iResolution = vResolution;

}
