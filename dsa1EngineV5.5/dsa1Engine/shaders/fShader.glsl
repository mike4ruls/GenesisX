#version 430

struct Light{
	vec3 lightPos;
	vec3 lightDir;
	vec3 Ambient;
	float lightIntensity;
	float lightRad;
};

layout (location = 10) uniform bool hasT;
layout (location = 11) uniform float lightIntensity;
layout (location = 12) uniform vec4 Ambient;
layout (location = 13) uniform vec4 Spec;
layout (location = 14) uniform float lightRad;
layout (location = 15) uniform Light lig[];
uniform sampler2D myTexture;

struct OutPut
{
	vec4 pos;
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
	const Light lights[] = lig;
	vec4 color;
	//color = vec4(1,0,0,1);
	color = input.color;
	//color = vec4(input.fragPos.xy,0.5+0.5*sin(time),1);
	//color = vec4(input.color.xy,input.color.z+1.0*cos(input.time),1);

	if(hasT)
	{
		color = texture(myTexture, input.uv);
	}
	color = color / 2;
	vec4 D = input.pos - input.lightPos;
	bool rendLight = false;
	
	float dist = dot(D,D);
	if(dist < lightRad)
	{
		rendLight = true;
	}

	if(rendLight)
	{
		float fade = (lightRad - dist) / lightRad; 

		vec4 L = input.lightPos - input.pos ;
		vec4 E = input.pos - input.camPos;
		vec4 H =  L+E;

		// SpotLight effect
		//float light =  clamp(dot(-L,input.norm),0.0, lightIntensity);

		// light intensity based on distance from light
		float light =   clamp(dot(L,input.norm),0.0,lightIntensity*fade);
		vec4 Specular = (Spec * color) * max(dot(H, input.norm),0.0);

		vec4 brightness = (Ambient + Specular) * light;

		//color = brightness;
		color += brightness;
		//color = input.norm;
	}

	gl_FragColor = color;
}