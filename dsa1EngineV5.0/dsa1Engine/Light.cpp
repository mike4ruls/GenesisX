#include "Light.h"



Light::Light()
{
}

Light::Light(char* name, float inten,glm::vec3 lightP, glm::vec3 lightD, void* r )
{
	sphere = new GameEntity(name,"models/sphere.obj", r);
	sphere->SetTag("Light");
	lightPos = lightP;
	lightDir = lightD;
	ambient = glm::vec4(0.0f,0.0f,0.0f,0.0f);
	lightIntensity = inten;
	lightRadius = 7.0f;
	//lightRadius = 10.0f;
	sphereSize = 0.5f;

	sphere->Translate(lightPos);
	sphere->Scale(sphereSize);
}


Light::~Light()
{
}
