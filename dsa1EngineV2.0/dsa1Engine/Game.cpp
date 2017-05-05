#include "Game.h"

Game::Game()
{
	CreateMeshes();
	rend = Renderer(gameobj);
}


Game::~Game()
{
}

void Game::CreateMeshes()
{
	// Making a mesh
	std::vector<Vertex> verts = { { glm::vec3(-0.5f,-0.5f,0.0f) },
	{ glm::vec3(-0.5f,0.5f,0.0f) },
	{ glm::vec3(0.5f,0.5f,0.0f) },
	{ glm::vec3(0.5f,-0.5f,0.0f) } };
	std::vector<unsigned int> ind = { 0,1,2,0,2,3 };
	//Mesh m = Mesh(verts, ind);
	// making a game obj
	gameobj.push_back(GameEntity("Pizza", verts, ind));
}

void Game::Update()
{
	for(unsigned int i = 0; i < gameobj.size(); i++)
	{
		gameobj[i].Update();
	}
	rend.Update();
}
