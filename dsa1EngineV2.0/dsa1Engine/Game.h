#pragma once
#include "Engine.h"
#include "GameEntity.h"
#include "Renderer.h"
class Game
{
public:
	Game();
	~Game();

	void CreateMeshes();
	void Update();

	std::vector<GameEntity> gameobj;
	Renderer rend;
private:

};

