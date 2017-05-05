#include "Game.h"

Game::Game(Renderer *r)
{
	rend = r;
	CreateMeshes();
}


Game::~Game()
{
	for(unsigned int i = 0; i < gameobj.size();i++)
	{
		if (gameobj[i] != nullptr) { delete gameobj[i]; gameobj[i] = nullptr; }
	}
}

void Game::CreateMeshes()
{
	// Making a mesh
	std::vector<Vertex> verts = { { glm::vec3(-0.5f,-0.5f,0.0f) },
	{ glm::vec3(-0.5f,0.5f,0.0f) },
	{ glm::vec3(0.5f,0.5f,0.0f) },
	{ glm::vec3(0.5f,-0.5f,0.0f) } };
	std::vector<unsigned int> ind = { 0,1,2,0,2,3 };

	std::vector<Vertex> verts2 = { { glm::vec3(-0.5f,-0.5f,0.0f) },
	{ glm::vec3(-0.5f,0.5f,0.0f) },
	{ glm::vec3(1.0f,-1.0f,0.0f) },
	{ glm::vec3(1.0f,-2.5f,0.0f) } };
	std::vector<unsigned int> ind2 = { 0,1,2,0,2,3 };

	// making a game obj
	gameobj.push_back(new GameEntity("Pizza", verts, ind, rend));
	gameobj.push_back(new GameEntity("poop", verts2, ind2, rend));
}

void Game::Update()
{
	for(unsigned int i = 0; i < gameobj.size(); i++)
	{
		(gameobj)[i]->Update();
	}
	rend->Update();
}
