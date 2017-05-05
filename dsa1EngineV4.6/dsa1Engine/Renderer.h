#pragma once
#include <vector>
#include "ShaderManager.h"
#include <GL\glew.h>
#include "GameEntity.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	void Update(GLuint program);
	unsigned int AddToRenderer(GameEntity &obj);
	void RemoveFromRenderer(unsigned int pos);

	std::vector<GameEntity*> gameObjs;
private:

};

