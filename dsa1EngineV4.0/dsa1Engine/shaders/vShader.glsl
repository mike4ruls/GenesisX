#version 430

layout (location = 0) in struct Vertex
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	vec4 color;
} input;

layout (location = 4) uniform mat4 worldPos;
layout (location = 5) uniform mat4 view;
layout (location = 6) uniform mat4 proj;
layout (location = 7) uniform float t;

out vec3 fragPos;
out vec4 color;
out float time;

void main()
{
	mat4 worldViewProj = proj * view * worldPos;
	fragPos = input.position;
	color = input.color;
	time = t;
	gl_Position = worldViewProj*vec4(input.position, 1);	
}
