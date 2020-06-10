#version 450

vec3 SkyColour = vec3(186.0f / 255.0f, 214.0f / 255.0f, 254.0f / 255.0f);

in vec3 fTexCoord;

out vec4 oColour;

float near = 0.1;
float far = 1000;


void main()
{             
    float ndc = gl_FragCoord.z * 2.0 - 1.0;
    float depth = (2.0 * near * far) / (far + near - ndc * (far - near));	

    oColour = vec4(vec3(depth / far), 1.0);
}