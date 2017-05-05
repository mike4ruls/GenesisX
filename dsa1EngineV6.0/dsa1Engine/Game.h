#pragma once
#include "InputManager.h"
#include "Renderer.h"
#include "Light.h"
class Game
{
public:
	Game(Renderer &r, InputManager &ip);
	~Game();

	void CreateMeshes();
	//bool CanRenderLights(GameEntity obj, Light light);
	void Update(GLuint program);
	void LightingPass(glm::vec3 camPos);

	InputManager *input;
	Renderer* rend;
	Light light1;

	std::vector<GameEntity*> gameobj;
private:

};

