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
	glm::vec4 red = {1.0f,0.0f,0.0f,1.0f};
	glm::vec4 green = { 0.0f,1.0f,0.0f,1.0f };
	glm::vec4 blue = { 0.0f,0.0f,1.0f,1.0f };
	glm::vec3 normal = {1.0f,0.0f,0.0f};
	glm::vec2 uv = { 0.0f,0.0f };

	// Making a mesh
	std::vector<Vertex> verts = { { glm::vec3(-0.2f,-0.2f,0.0f), uv, normal, red},// Bottom Left
	{ glm::vec3(-0.2f,0.2f,0.0f), uv, normal, red },// Top Left
	{ glm::vec3(0.2f,0.2f,0.0f), uv, normal, red },// Top Right
	{ glm::vec3(0.2f,-0.2f,0.0f), uv, normal, red } };// Bottom Right
	std::vector<unsigned int> ind = { 0,1,2,0,2,3 };

	std::vector<Vertex> verts2 = { { glm::vec3(-0.5f,-0.5f,0.0f), uv, normal, red }, // Bottom Left
	{ glm::vec3(-0.5f,-0.3f,0.0f), uv, normal, red },// Top Left
	{ glm::vec3(0.5f,-0.3f,0.0f), uv, normal, red },// Top Right
	{ glm::vec3(0.5f,-0.5f,0.0f), uv, normal, red } };// Bottom Right
	std::vector<unsigned int> ind2 = { 0,1,2,0,2,3 };

	// making a game obj
	gameobj.push_back(new GameEntity("Pizza", verts, ind, rend));
	gameobj.push_back(new GameEntity("poop", verts2, ind2, rend));
}

void Game::Update(GLuint program)
{
	for(unsigned int i = 0; i < gameobj.size(); i++)
	{
		(gameobj)[i]->Update();
	}
	(gameobj)[0]->Translate(glm::sin(Engine::time.t) * Engine::time.dt,0.0f,0.0f);
	rend->Update(program);
}
