#pragma once
#include <vector>
#include <GL\glew.h>
#include <FreeImage.h>
#include "GameEntity.h"
class Renderer
{
public:
	Renderer();
	Renderer(std::vector<GameEntity> &go);
	~Renderer();

	void Update();

	std::vector<GameEntity> gameObjs;
private:

};

