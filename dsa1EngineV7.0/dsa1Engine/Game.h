#pragma once
#include "InputManager.h"
#include "Renderer.h"
#include "Light.h"
class Game
{
public:
	Game(Renderer &r, InputManager &ip);
	~Game();

	//game methods
	void CreateMeshes();
	void Update();
	void RenderLights();
	void UnrenderLights();

	InputManager *input;
	Renderer* rend;

	std::vector<GameEntity*> gameobj;
	std::vector<Light*> lights;
private:

};

