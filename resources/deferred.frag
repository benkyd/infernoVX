#version 450

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gAlbedo;
layout (location = 2) out vec3 gSurfaceNormal;
layout (location = 3) out vec3 gTexCoord;

in vec3 fColour;
in vec3 fTexCoord;

// float near = 0.1;
// float far = 10;
// float ndc = gl_FragCoord.z * 2.0 - 1.0;
// float depth = (2.0 * near * far) / (far + near - ndc * (far - near));	
// depth = depth / far;

void main()
{
    gPosition = fColour.rgb;
	gAlbedo = vec3(0);
	gSurfaceNormal = vec3(0);
	gTexCoord = fTexCoord;
}
