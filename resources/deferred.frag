#version 450

in vec3 fTexCoord;

out vec4 oColour;

float near = 0.1;
float far = 10;


void main()
{             
    float ndc = gl_FragCoord.z * 2.0 - 1.0;
    float depth = (2.0 * near * far) / (far + near - ndc * (far - near));	

    oColour = vec4(vec3(depth / far), 1.0);
}
