#pragma once
#include "GameEntity.h"
class Light
{
public:
	Light();
	Light(char* name, glm::vec3 lightP, glm::vec3 lightD, void* r);
	~Light();

	glm::vec3 lightPos;
	glm::vec3 lightDir;
	float sphereSize;

	GameEntity* sphere;
private:

};

