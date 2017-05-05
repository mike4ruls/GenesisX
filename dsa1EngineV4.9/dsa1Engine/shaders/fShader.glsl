#version 430
layout (location = 10) uniform bool hasT;
uniform sampler2D myTexture;

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
in OutPut input;


void main()
{
	vec4 color;
	//color = vec4(1,0,0,1);
	color = input.color;
	//color = vec4(input.fragPos.xy,0.5+0.5*sin(time),1);
	//color = vec4(input.color.xy,input.color.z+1.0*cos(input.time),1);

	if(hasT)
	{
		color = texture(myTexture, input.uv);
	}

	vec4 L = input.fragPos - input.lightPos;
	vec4 E = input.fragPos - input.camPos;
	vec4 H =  L + E;

	vec4 Ambient = vec4(0.5, 0.5, 0.5, 0.0);
	vec4 Diffuse = color * max(dot(L,normalize(input.norm)),0);
	vec4 Specular = vec4(0.01, 0.01, 0.01, 0.01) * max(dot(H, normalize(input.norm)),0);

	vec4 brightness = Ambient + Diffuse + Specular;

	//gl_FragColor = color;
	//gl_FragColor = color * Ambient;
	//gl_FragColor = color * Diffuse;
	//gl_FragColor = color * Specular;
	gl_FragColor = color * brightness;
}