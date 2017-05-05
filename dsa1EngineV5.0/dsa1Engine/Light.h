#pragma once
#include "GameEntity.h"
class Light
{
public:
	Light();
	Light(char* name, float inten,glm::vec3 lightP, glm::vec3 lightD, void* r);
	~Light();

	glm::vec3 lightPos;
	glm::vec3 lightDir;
	glm::vec4 ambient;
	float lightIntensity;
	float sphereSize;
	float lightRadius;

	GameEntity* sphere;
private:

};

