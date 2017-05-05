#pragma once
#include <vector>
#include "ShaderManager.h"
#include <GL\glew.h>
#include "Camera.h"
#include "GameEntity.h"


class Renderer
{
public:
	Renderer(Camera *c);
	~Renderer();

	void Update(GLuint program);
	unsigned int AddToRenderer(GameEntity &obj);
	void RemoveFromRenderer(unsigned int pos);

	Camera* cam;
	glm::vec3 lightPos;

	std::vector<GameEntity*> gameObjs;
private:

};

