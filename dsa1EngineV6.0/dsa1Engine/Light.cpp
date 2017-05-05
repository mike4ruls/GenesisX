#include "Light.h"



Light::Light()
{
}

Light::Light(char* name, float inten,glm::vec3 lightP, glm::vec3 lightD, void* r )
{
	sphere = new GameEntity(name,"models/sphere.obj", r);
	sphere->SetTag("Light");
	myLight.lightPos = lightP;
	myLight.lightDir = lightD;
	myLight.color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	myLight.lightIntensity = inten;
	myLight.linear = 0.0;
	myLight.quadratic = 0.2;
	GLfloat constant = 1.0;
	GLfloat lightMax = std::fmaxf(std::fmaxf(myLight.color.r, myLight.color.g), myLight.color.b);;
	GLfloat radius = (-myLight.linear + std::sqrtf(myLight.linear*myLight.linear - 4 * myLight.quadratic *(constant - (256.0 / 5.0) * lightMax))) / (2 * myLight.quadratic);
	myLight.lightRadius = radius;
	printf("%f", myLight.lightRadius);
	sphere->Translate(myLight.lightPos);
	sphere->Scale(myLight.lightRadius);
}


Light::~Light()
{
}
