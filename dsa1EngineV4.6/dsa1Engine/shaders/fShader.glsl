#version 430
layout (location = 8) uniform bool hasT;
uniform sampler2D myTexture;

in vec3 fragPos;
in vec2 uv;
in vec4 color;
in float time;
void main()
{

	//gl_FragColor = vec4(1,0,0,1);
	//gl_FragColor = color;
	//gl_FragColor = vec4(fragPos.xy,0.5+0.5*sin(time),1);
	gl_FragColor = vec4(color.xy,color.z+1.0*cos(time),1);
	if(hasT)
	{
		gl_FragColor = texture(myTexture, uv);
	}
}