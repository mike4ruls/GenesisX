#version 430

layout (location = 2) uniform sampler2D color_Text;

in vec2 TextCoord;
out vec4 color;

void main()
{
	vec4 newcolor;

	newcolor = texture(color_Text, TextCoord);
	newcolor = newcolor/3;

	color = newcolor;
}