#pragma once
#include <vector>
#include <GL\glew.h>
#include <FreeImage.h>
#include "GameEntity.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	void Update();
	unsigned int AddToRenderer(GameEntity &obj);
	void RemoveFromRenderer(unsigned int pos);

	std::vector<GameEntity*> gameObjs;
private:

};

