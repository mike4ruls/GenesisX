#include "Game.h"

Game::Game(Renderer &r, InputManager &ip)
{
	rend = &r;
	input = &ip;
	bullets.reserve(20);
	gameobj.reserve(10);
	lights.reserve(20);
	lights.push_back(new Light("Light1", 1.0f, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light2", 1.0f, glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light3", 1.0f, glm::vec3(10, 1, 0), glm::vec3(0, 0, 0), rend));
	lights.push_back(new Light("Light4", 1.0f, glm::vec3(10, 5, 0), glm::vec3(0, 0, 0), rend));

	lights[0]->myLight.color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);
	lights[2]->myLight.color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);
	lights[3]->myLight.color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);
	lights[1]->myLight.color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);

	UnrenderLights();

	//rend->RemoveFromRenderer(light1->sphere.rendID);

	CreateMeshes();
}


Game::~Game()
{
	for(unsigned int i = 0; i < gameobj.size();i++)
	{
		//if (gameobj[i] != nullptr) { delete gameobj[i]; gameobj[i] = nullptr; }
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
	std::vector<Vertex> verts = { { glm::vec3(-0.2f,-0.2f,0.0f), uv, normal},// Bottom Left
	{ glm::vec3(-0.2f,0.2f,0.0f), uv, normal},// Top Left
	{ glm::vec3(0.2f,0.2f,0.0f), uv, normal},// Top Right
	{ glm::vec3(0.2f,-0.2f,0.0f), uv, normal} };// Bottom Right
	std::vector<unsigned int> ind = { 0,2,1,0,3,2 };

	std::vector<Vertex> verts2 = { { glm::vec3(-0.5f,-0.5f,0.0f), uv, normal }, // Bottom Left
	{ glm::vec3(-0.5f,-0.3f,0.0f), uv, normal},// Top Left
	{ glm::vec3(0.5f,-0.3f,0.0f), uv, normal },// Top Right
	{ glm::vec3(0.5f,-0.5f,0.0f), uv, normal } };// Bottom Right
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
	
	//bulletMesh = Mesh("models/box.obj", Mesh::SingleMesh);
	bulletMesh = Mesh("models/Sphere.obj", Mesh::SingleMesh);

	// making a game obj
	//gameobj.push_back(new GameEntity("pizza", verts, ind, rend));
	//gameobj.push_back(new GameEntity("pizza2", verts2, ind2, rend));
	//gameobj.push_back(new GameEntity("too much pizza", "models/DestinyIsland/level/di00_01.obj", Mesh::MultipleMesh, rend));
	//gameobj.push_back(new GameEntity("too much pizza", "models/TraverseTown/level/tw00_01.obj", Mesh::MultipleMesh, rend));
	gameobj.push_back(new GameEntity("The floor", "models/plane.obj", Mesh::SingleMesh, rend));
	gameobj.push_back(new GameEntity("My box","models/box.obj", Mesh::SingleMesh, rend));
	gameobj.push_back(new GameEntity("Big ass wall", "models/plane.obj", Mesh::SingleMesh, rend));
	//gameobj.push_back(new GameEntity("too much pizza", "models/plane.obj", Mesh::SingleMesh, rend));
	//gameobj.push_back(new GameEntity("lots pizza", "models/HaloSword.obj", Mesh::SingleMesh, rend));


	//gameobj[0]->SetTag("MultiMesh");
	//gameobj[0]->Scale(0.05f);
	//gameobj[0]->Rotate(3.038f, 0, 0);
	gameobj[0]->Scale(100.0f);
	gameobj[0]->objMesh.LoadTexture("models/textures/brick.jpg");
	//gameobj[0]->SetTag("Floor");
	//
	//
	gameobj[1]->objMesh.LoadTexture("models/textures/raygunUVTest.tga");
	//
	gameobj[1]->Translate(0, 3.5f, 0);
	//
	gameobj[2]->Rotate(1.5, 0, 0);
	gameobj[2]->Scale(2.0f);
	gameobj[2]->Translate(4, 3, -4);
	//gameobj[2]->SetTag("Wall");

	//gameobj[3]->objMesh.LoadTexture("models/textures/brick.jpg");
	
}

void Game::Update()
{
	float speed = 0.25f;
	if (input->IsKeyDown(GLFW_KEY_LEFT))
	{
		//gameobj[1]->ApplyForce(glm::vec3(-speed, 0.0f, 0.0f));
	}
	if (input->IsKeyDown(GLFW_KEY_RIGHT))
	{
		//gameobj[1]->ApplyForce(glm::vec3(speed, 0.0f, 0.0f));
	}
	if (input->IsKeyDown(GLFW_KEY_UP))
	{
		//gameobj[1]->ApplyForce(glm::vec3(0.0f, 0.0f, -speed));
	}
	if (input->IsKeyDown(GLFW_KEY_DOWN))
	{
		//gameobj[1]->ApplyForce(glm::vec3(0.0f, 0.0f, speed));
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
	if (input->IsMouseClick(GLFW_MOUSE_BUTTON_2))
	{
		//printf("Mouse CLICKUUUUUU");
		currentMouseClick = true;
	}
	if (currentMouseClick == true && previousMouseClick == false)
	{
		Shoot();
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
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
		for (unsigned int j = 0; j < gameobj.size(); j++)
		{
			if(gameobj[j]->GetTag() == "GameObject")
			{
				if(SphereBoxCollision(bullets[i]->bulletModel,gameobj[j]))
				{
					bullets[i]->destroyBullet = true;
				}
			}
		}
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->destroyBullet)
		{

			//rend->RemoveFromRenderer(bullets[i]->bulletModel->rendID);
			//rend->RemoveFromRenderer(bullets[i]->bulletLight->sphere->rendID);
			//rend->RemoveFromLights(bullets[i]->bulletLight->lightID);

			bullets[i]->bulletModel->SetTag("GameObject");
			bullets[i]->bulletModel->ridgidBody.velocity = glm::vec3(0);
			bullets[i]->bulletModel->applyGrav = false;
			gameobj.push_back(bullets[i]->bulletModel);
			bullets.erase(bullets.begin() + bullets[i]->bulletID);
			for (unsigned int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->bulletID = i;
			}

			//if (bulletHolder != nullptr) { delete bulletHolder;  bulletHolder = nullptr; }
		}
	}
	//(gameobj)[0]->Translate(sin(Engine::time.t)/20.0f,0.0f,0.0f);
	//gameobj[0]->Scale(abs(sin(Engine::time.t))/5.0f);
	//gameobj[0]->Rotate(1.0f*Engine::time.dt, 2.0f*Engine::time.dt, 0.0f);
	//gameobj[1]->Rotate(0.0f, 2.0f*Engine::time.dt, 0.0f);

	previousMouseClick = currentMouseClick;
	currentMouseClick = false;
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

bool Game::SphereCollision(GameEntity *obj1, GameEntity *obj2)
{
	float radius1 = obj1->collider.radius;
	float radius2 = obj2->collider.radius;

	glm::vec3 center1 = obj1->transform.position;
	glm::vec3 center2 = obj2->transform.position;
	glm::vec3 distance = center2 - center1;

	float dist = glm::length(distance);

	if(dist <= (radius1 + radius2))
	{
		return true;
	}
	return false;
}

bool Game::BoxCollision(GameEntity *obj1, GameEntity *obj2)
{
	return false;
}

bool Game::SphereBoxCollision(GameEntity * sphere, GameEntity * box)
{
	float sphereRadius = sphere->collider.radius;
	glm::vec3 sphereCenter = sphere->transform.position;

	glm::vec3 boxX = glm::vec3(box->collider.boundingBox.x + box->transform.position.x, box->transform.position.y, box->transform.position.z);
	glm::vec3 boxY = glm::vec3(box->transform.position.x, box->collider.boundingBox.y + box->transform.position.y, box->transform.position.z);
	glm::vec3 boxZ = glm::vec3(box->transform.position.x, box->transform.position.y, box->collider.boundingBox.z + box->transform.position.z);
	glm::vec3 distanceX = boxX - sphereCenter;
	glm::vec3 distanceY = boxY - sphereCenter;
	glm::vec3 distanceZ = boxZ - sphereCenter;

	glm::vec3 distanceFlipX = (boxX * -1.0f) - sphereCenter;
	glm::vec3 distanceFlipY = (boxY * -1.0f) - sphereCenter;
	glm::vec3 distanceFlipZ = (boxZ * -1.0f) - sphereCenter;

	float distX = glm::length(distanceX);
	float distY = glm::length(distanceY);
	float distZ = glm::length(distanceZ);

	float distFlipX = glm::length(distanceFlipX);
	float distFlipY = glm::length(distanceFlipY);
	float distFlipZ = glm::length(distanceFlipZ);

	if (distX <= sphereRadius || distFlipX <= sphereRadius)
	{
		return true;
	}
	if (distY <= sphereRadius || distFlipY <= sphereRadius)
	{
		return true;
	}
	if (distZ <= sphereRadius || distFlipZ <= sphereRadius)
	{
		return true;
	}
	return false;
}

void Game::Shoot()
{
	bullets.push_back( new Bullet(30,&bulletMesh, rend));
}

