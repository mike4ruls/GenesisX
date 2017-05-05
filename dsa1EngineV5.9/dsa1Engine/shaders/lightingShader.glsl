#version 430

layout (location = 2) uniform vec4 camPos;
layout (location = 3) uniform vec4 lightPos;
layout (location = 4) uniform float lightIntensity;
layout (location = 5) uniform vec4 lightCol;
//layout (location = 4) uniform vec4 Spec;
layout (location = 6) uniform float lightRad;

layout (location = 7) uniform sampler2D color_Text;
layout (location = 8) uniform sampler2D normal_Text;
layout (location = 9) uniform sampler2D worldPos_Text;

in vec2 TextCoord;
out vec4 color;

void main()
{
	vec4 newcolor;
	vec4 norm;
	vec4 pos;

	newcolor = texture(color_Text, TextCoord);
	norm = texture(normal_Text, TextCoord);
	pos = texture(worldPos_Text, TextCoord);
	newcolor = newcolor/2; 
	
	vec4 L = normalize(lightPos - pos);
	vec4 E = normalize(camPos - pos);
	vec4 H =  normalize(L+E);
	
	// light intensity based on distance from light
	float ambience = 0.1;
	float diffuse = clamp(dot(L,norm),0.0,1.0);
	float specular = pow(max(dot(H, norm),0.0), 16);
	
	float lightIntensity =  ambience + diffuse + specular;
	 
	vec4 lighting = lightCol * lightIntensity;
	
	newcolor += vec4(newcolor.rgb * lighting.rgb, newcolor.a);

	
	//gl_FragColor = color;
	//color = vec4(1,0,0,1);
	color = newcolor;
	//color = norm;
	//color = pos;
}