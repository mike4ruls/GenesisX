#version 430

layout (location = 0) in struct Vertex
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	vec4 color;
} Input;

layout (location = 4) uniform mat4 worldPos;
layout (location = 5) uniform mat4 view;
layout (location = 6) uniform mat4 proj;
layout (location = 7) uniform float t;
layout (location = 8) uniform vec3 camP;
layout (location = 9) uniform vec3 lPos;

struct OutPut
{
	vec4 fragPos;
	vec4 camPos;
	vec4 lightPos;
	vec4 norm;
	vec2 uv;
	vec4 color;
	float time;
};
out OutPut input;


void main()
{
		mat4 worldViewProj = proj * view * worldPos;
		input.fragPos = worldViewProj * vec4(Input.position, 1);
		input.camPos = vec4(camP, 1);
		input.lightPos = vec4(lPos, 1);
		//input.norm = worldViewProj*vec4(Input.normal,0);
		input.norm = transpose(inverse(worldViewProj))*vec4(Input.normal,0);
		input.uv = Input.uv;
		input.color = Input.color;
		input.time = t;

		gl_Position = worldViewProj*vec4(Input.position, 1);	
}
