#pragma once
#include "Renderer.h"
class Game
{
public:
	Game(Renderer *r);
	~Game();

	void CreateMeshes();
	void Update();

	Renderer* rend;

	std::vector<GameEntity*> gameobj;
private:

};

