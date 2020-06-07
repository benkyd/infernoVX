#version 450

vec3 SkyColour = vec3(186.0f / 255.0f, 214.0f / 255.0f, 254.0f / 255.0f);

in vec3 fTexCoord;
in float fDistance;

out vec4 oColour;

void main() {

	oColour = vec4(.9, .9, .9, 1);

	if (oColour.w == .0)
		discard;
	
	float fogMax = 60000;
	
	vec3 colour = mix(oColour.xyz, SkyColour, min(1.0f, fDistance / fogMax));

	// Retain fragment transparency
	oColour = vec4(colour, oColour.w);

}
