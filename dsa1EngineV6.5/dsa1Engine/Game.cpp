#include "Game.h"

Game::Game(Renderer &r, InputManager &ip)
{
	rend = &r;
	input = &ip;
	lights.push_back(new Light("Light1", 1.0f, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light2", 1.0f, glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light3", 1.0f, glm::vec3(10, 1, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light4", 1.0f, glm::vec3(10, 5, 0), glm::vec3(0, 0, 0), rend));

	UnrenderLights();

	//rend->RemoveFromRenderer(light1->sphere.rendID);

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
	//gameobj.push_back(new GameEntity("pizza", verts, ind, rend));
	//gameobj.push_back(new GameEntity("pizza2", verts2, ind2, rend));
	gameobj.push_back(new GameEntity("too much pizza", "models/plane.obj", rend));
	gameobj.push_back(new GameEntity("more pizza","models/box.obj", rend));
	gameobj.push_back(new GameEntity("big ass wall", "models/plane.obj", rend));
	//gameobj.push_back(new GameEntity("too much pizza", "models/raygun.obj", rend));
	//gameobj.push_back(new GameEntity("lots pizza", "models/HaloSword.obj", rend));

	// setting box settings
	gameobj[0]->Scale(100.0f);
	//gameobj[0]->Translate(0, 0, 0.5f);
	gameobj[0]->objMesh.LoadTexture("models/textures/brick.jpg");
	//gameobj[0]->ridgidBody.mass = 1.2f;

	//// setting teapot settings
	//gameobj[1]->Translate(0,1,0);
	//gameobj[1]->ridgidBody.mass = 0.9f;
	//gameobj[1]->objMesh.specular = {10,10,10,10};

	//// setting raygun settings
	gameobj[1]->objMesh.LoadTexture("models/textures/raygunUVTest.tga");
	////gameobj[4]->objMesh.LoadTexture("models/textures/brick.jpg");
	//gameobj[4]->objMesh.specular = { 4,4,4,4 };
	gameobj[1]->Translate(0, 3.5f, 0);

	gameobj[2]->Rotate(1.5, 0, 0);
	gameobj[2]->Scale(2.0f);
	gameobj[2]->Translate(4, 3, -4);
	//gameobj[4]->parent = gameobj[3];

	//gameobj[5]->objMesh.specular = { 11,11,11,11 };
	//gameobj[5]->Rotate(0, 1.5, 0);
	//gameobj[5]->Scale(0.1f);
	
}

void Game::Update()
{
	float speed = 0.25f;
	if (input->IsKeyDown(GLFW_KEY_LEFT))
	{
		gameobj[1]->ApplyForce(glm::vec3(-speed, 0.0f, 0.0f));
	}
	if (input->IsKeyDown(GLFW_KEY_RIGHT))
	{
		gameobj[1]->ApplyForce(glm::vec3(speed, 0.0f, 0.0f));
	}
	if (input->IsKeyDown(GLFW_KEY_UP))
	{
		gameobj[1]->ApplyForce(glm::vec3(0.0f, 0.0f, -speed));
	}
	if (input->IsKeyDown(GLFW_KEY_DOWN))
	{
		gameobj[1]->ApplyForce(glm::vec3(0.0f, 0.0f, speed));
	}
	if (input->IsKeyDown(GLFW_KEY_LEFT_BRACKET))
	{
		//gameobj[5]->Rotate(0.0f,-0.1f,0.0f);
	}
	if (input->IsKeyDown(GLFW_KEY_RIGHT_BRACKET))
	{
		//gameobj[5]->Rotate(0.0f, 0.1f, 0.0f);
	}
	if (input->IsKeyDown(GLFW_KEY_O))
	{
		lights[0]->myLight.lightRadius -= 0.1f;
	}
	if (input->IsKeyDown(GLFW_KEY_P))
	{
		lights[0]->myLight.lightRadius += 0.1f;
	}
	if (input->IsKeyPressed(GLFW_KEY_TAB))
	{
		rend->ChangeSkyBox();
	}
	if (input->IsKeyDown(GLFW_KEY_0))
	{
		lights[0]->myLight.color = { 1.0f,1.0f,1.0f,1.0f };

		lights[1]->myLight.color = { 1.0f,0.0f,0.0f,1.0f };
		lights[2]->myLight.color = { 0.0f,1.0f,0.0f,1.0f };
		lights[3]->myLight.color = { 0.0f,0.0f,1.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_1))
	{
		lights[0]->myLight.color = { 1.0f,0.0f,0.0f,1.0f };

		lights[2]->myLight.color = { 1.0f,0.0f,0.0f,1.0f };
		lights[3]->myLight.color = { 0.0f,1.0f,0.0f,1.0f };
		lights[1]->myLight.color = { 0.0f,0.0f,1.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_2))
	{
		lights[0]->myLight.color = { 0.0f,1.0f,0.0f,1.0f };

		lights[3]->myLight.color = { 1.0f,0.0f,0.0f,1.0f };
		lights[1]->myLight.color = { 0.0f,1.0f,0.0f,1.0f };
		lights[2]->myLight.color = { 0.0f,0.0f,1.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_3))
	{
		lights[0]->myLight.color = { 0.0f,0.0f,1.0f,1.0f };

		lights[1]->myLight.color = { 1.0f,0.0f,0.0f,1.0f };
		lights[2]->myLight.color = { 0.0f,1.0f,0.0f,1.0f };
		lights[3]->myLight.color = { 1.0f,1.0f,1.0f,1.0f };
	}


	if (input->IsKeyPressed(GLFW_KEY_G))
	{
		for (unsigned int i = 0; i < gameobj.size(); i++)
		{
			if ((gameobj)[i]->applyGrav)
			{
				(gameobj)[i]->applyGrav = false;
			}
			else
			{
				(gameobj)[i]->applyGrav = true;
			}
		}
	}
	for(unsigned int i = 0; i < gameobj.size(); i++)
	{
		(gameobj)[i]->Update();
		
	}
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		(lights)[i]->Move(sin(Engine::time.t) / 10.0f, cos(Engine::time.t) / 10.0f,0);
		//(lights)[i]->myLight.color += glm::vec4(sin(Engine::time.t * 3) / 20.0f, cos(Engine::time.t * 3) / 20.0f, sin(Engine::time.t * 3) / 20.0f,1.0);
	}

	//(gameobj)[0]->Translate(sin(Engine::time.t)/20.0f,0.0f,0.0f);
	//gameobj[0]->Scale(abs(sin(Engine::time.t))/5.0f);
	//gameobj[0]->Rotate(1.0f*Engine::time.dt, 2.0f*Engine::time.dt, 0.0f);
	//gameobj[1]->Rotate(0.0f, 2.0f*Engine::time.dt, 0.0f);
}

void Game::RenderLights()
{
	for (unsigned int i = 0; i < lights.size(); i++) {
		rend->AddToRenderer(*lights[i]->sphere);
	}
}

void Game::UnrenderLights()
{
	for (unsigned int i = 0; i < lights.size(); i++) {
		rend->RemoveFromRenderer(lights[i]->sphere->rendID);
	}
}

