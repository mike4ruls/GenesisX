#pragma once
#include "Renderer.h"
class Game
{
public:
	Game(Renderer *r);
	~Game();

	void CreateMeshes();
	void Update(GLuint program);

	Renderer* rend;

	std::vector<GameEntity*> gameobj;
private:

};

