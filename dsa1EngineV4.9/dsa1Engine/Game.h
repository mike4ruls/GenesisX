#pragma once
#include "Renderer.h"
#include "Light.h"
class Game
{
public:
	Game(Renderer *r);
	~Game();

	void CreateMeshes();
	void Update(GLuint program);

	Renderer* rend;
	Light light1;

	std::vector<GameEntity*> gameobj;
private:

};

