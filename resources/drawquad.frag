#version 450
 
out vec4 oColour;

in vec2 fTexCoord;

uniform sampler2D Texture;

void main()
{ 
	oColour = texture(Texture, fTexCoord);
	// oColour = vec4(fTexCoord, 0.0f, 1.0f);
}
