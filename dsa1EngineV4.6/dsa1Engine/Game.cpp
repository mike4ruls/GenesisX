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
	glm::vec4 purple = { 1.0f,0.0f,1.0f,1.0f };
	glm::vec3 normal = {1.0f,0.0f,0.0f};
	glm::vec2 uv = { 0.0f,0.0f };

	// Making a mesh
	std::vector<Vertex> verts = { { glm::vec3(-0.2f,-0.2f,0.0f), uv, normal, green},// Bottom Left
	{ glm::vec3(-0.2f,0.2f,0.0f), uv, normal, green },// Top Left
	{ glm::vec3(0.2f,0.2f,0.0f), uv, normal, green },// Top Right
	{ glm::vec3(0.2f,-0.2f,0.0f), uv, normal, green } };// Bottom Right
	std::vector<unsigned int> ind = { 0,2,1,0,3,2 };

	std::vector<Vertex> verts2 = { { glm::vec3(-0.5f,-0.5f,0.0f), uv, normal, blue }, // Bottom Left
	{ glm::vec3(-0.5f,-0.3f,0.0f), uv, normal, red },// Top Left
	{ glm::vec3(0.5f,-0.3f,0.0f), uv, normal, green },// Top Right
	{ glm::vec3(0.5f,-0.5f,0.0f), uv, normal, purple } };// Bottom Right
	std::vector<unsigned int> ind2 = { 0,2,1,0,3,2 };

//	std::vector<Vertex> verts3 = { { glm::vec3(-0.2f,-0.2f,0.2f), uv, normal, purple },// Bottom Left
//	{ glm::vec3(-0.2f,0.2f,0.2f), uv, normal, purple },// Top Left
//	{ glm::vec3(0.2f,0.2f,0.2f), uv, normal, purple },// Top Right
//	{ glm::vec3(0.2f,-0.2f,0.2f), uv, normal, purple },// Bottom Right
//
//	{ glm::vec3(-0.2f, -0.2f, -0.2f), uv, normal, purple },// Bottom Left
//	{ glm::vec3(-0.2f,0.2f,-0.2f), uv, normal, purple },// Top Left
//	{ glm::vec3(0.2f,0.2f,-0.2f), uv, normal, purple },// Top Right
//	{ glm::vec3(0.2f,-0.2f,-0.2f), uv, normal, purple }
//};// Bottom Right
//	std::vector<unsigned int> ind3 = { 0,1,2,0,2,3, 4,5,1,4,1,0, 7,6,5,7,5,4, 3,2,6,3,6,7, 1,5,6,1,6,2, 4,0,3,4,3,7 };

	// making a game obj
	gameobj.push_back(new GameEntity("pizza", verts, ind, rend));
	gameobj.push_back(new GameEntity("pizza2", verts2, ind2, rend));
	gameobj.push_back(new GameEntity("more pizza","models/box.obj", rend));
	gameobj.push_back(new GameEntity("too much pizza", "models/teapot.obj", rend));
	gameobj.push_back(new GameEntity("too much pizza", "models/raygun.obj", rend));

	gameobj[2]->Scale(0.1f);
	gameobj[2]->Translate(0, 0, 0.5f);
	gameobj[2]->objMesh.LoadTexture("models/textures/brick.jpg");
	gameobj[3]->Translate(0,1,0);
	gameobj[4]->objMesh.LoadTexture("models/textures/raygunUVTest.tga");
	gameobj[4]->Translate(0, 0, 1);
	gameobj[4]->Rotate(0, 45, 0);
	gameobj[4]->Scale(0.1f);

}

void Game::Update(GLuint program)
{
	for(unsigned int i = 0; i < gameobj.size(); i++)
	{
		(gameobj)[i]->Update();
	}
	(gameobj)[0]->Translate(sin(Engine::time.t)/20.0f,0.0f,0.0f);
	gameobj[2]->Scale(abs(sin(Engine::time.t))/5.0f);
	gameobj[2]->Rotate(1.0f*Engine::time.dt, 2.0f*Engine::time.dt, 0.0f);
	gameobj[3]->Rotate(0.0f, 2.0f*Engine::time.dt, 0.0f);
	rend->Update(program);
}
