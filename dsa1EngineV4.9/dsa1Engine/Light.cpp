#include "Light.h"



Light::Light()
{
}

Light::Light(char* name, glm::vec3 lightP, glm::vec3 lightD, void* r )
{
	sphere = new GameEntity(name,"models/sphere.obj", r);
	sphere->SetTag("Light");
	lightPos = lightP;
	lightDir = lightD;
	sphereSize = 0.5f;

	sphere->Translate(lightPos);
	sphere->Scale(sphereSize);
}


Light::~Light()
{
}
