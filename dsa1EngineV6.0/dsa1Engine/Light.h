#pragma once
#include "GameEntity.h"
class Light
{
public:
	Light();
	Light(char* name, float inten,glm::vec3 lightP, glm::vec3 lightD, void* r);
	~Light();
	struct LightAttr{
		glm::vec3 lightPos;
		glm::vec3 lightDir;
		glm::vec4 color;
		float lightIntensity;
		float lightRadius;
		GLfloat linear;
		GLfloat quadratic;
	}myLight;

	GameEntity* sphere;
private:

};

