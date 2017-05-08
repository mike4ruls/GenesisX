#pragma once
#include "InputManager.h"
#include "Renderer.h"
#include "Light.h"
#include "Bullet.h"
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
	bool SphereCollision(GameEntity *obj1, GameEntity *obj2);
	bool BoxCollision(GameEntity *obj1, GameEntity *obj2);
	bool SphereBoxCollision(GameEntity *obj1, GameEntity *obj2);

	void Shoot();

	InputManager *input;
	Renderer* rend;

	Mesh bulletMesh;

	bool currentMouseClick;
	bool previousMouseClick;

	std::vector<GameEntity*> gameobj;
	std::vector<Bullet*> bullets;
	std::vector<Light*> lights;
private:

};

