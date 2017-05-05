#version 430
in vec3 fragPos;
in vec4 color;
in float time;
void main()
{
	//gl_FragColor = vec4(1,0,0,1);
	gl_FragColor = color;
	//gl_FragColor = vec4(fragPos.xy,0.5+0.5*sin(time),1);
}