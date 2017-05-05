#version 430

layout (location = 0) in struct Vertex
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	vec4 color;
} input;

layout (location = 4) uniform mat4 worldPos;
layout (location = 5) uniform float t;

out vec3 fragPos;
out vec4 color;
out float time;

void main()
{
	fragPos = input.position;
	color = input.color;
	time = t;
	gl_Position = worldPos*vec4(input.position, 1);	
}
