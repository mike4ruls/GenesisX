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
	myLight.lightRadius = 7.0f;
	//lightRadius = 10.0f;
	sphereSize = 0.5f;

	sphere->Translate(myLight.lightPos);
	sphere->Scale(sphereSize);
}


Light::~Light()
{
}
