#version 450
 
out vec4 oColour;

in vec2 fTexCoord;

uniform sampler2D Texture;

void main()
{ 
    oColour = texture(Texture, fTexCoord);
}
