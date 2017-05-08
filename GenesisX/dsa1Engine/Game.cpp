#include "Game.h"

Game::Game(Renderer &r, InputManager &ip)
{
	rend = &r;
	input = &ip;
	bullets.reserve(20);
	gameobj.reserve(10);
	lights.reserve(20);
	CreateMeshes();
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
	//Engine::LoadMesh("DestinyIsland", "models/DestinyIsland/level/di00_01.obj", Mesh::MultipleMesh, "models/DestinyIsland/level/");
	//Engine::LoadMesh("TraverseTown", "models/TraverseTown/level/tw00_01.obj", Mesh::MultipleMesh, "models/TraverseTown/level/");
	Engine::LoadMesh("RayGun", "models/raygun.obj", Mesh::SingleMesh, "");
	Engine::LoadMesh("HaloSword","models/HaloSword.obj", Mesh::SingleMesh, "");
	Engine::LoadMesh("Teapot", "models/teapot.obj", Mesh::SingleMesh, "");
	Engine::LoadMesh("Sphere", "models/sphere.obj", Mesh::SingleMesh, "");
	Engine::LoadMesh("Box", "models/box.obj", Mesh::SingleMesh, "");
	Engine::LoadMesh("Plane", "models/plane.obj", Mesh::SingleMesh, "");

	// making a game obj
	//gameobj.push_back(new GameEntity("too much pizza", "models/DestinyIsland/level/di00_01.obj", Mesh::MultipleMesh, rend));
	//gameobj.push_back(new GameEntity("too much pizza", "models/TraverseTown/level/tw00_01.obj", Mesh::MultipleMesh, rend));
	gameobj.push_back(new GameEntity("The floor", Engine::GetMesh("Plane"), rend));
	gameobj.push_back(new GameEntity("My box", Engine::GetMesh("Box"), rend));
	gameobj.push_back(new GameEntity("Big ass wall", Engine::GetMesh("Plane"), rend));

	//gameobj[0]->SetTag("MultiMesh");
	//gameobj[0]->Scale(0.05f);
	//gameobj[0]->Rotate(3.038f, 0, 0);
	gameobj[0]->Scale(100.0f);
	gameobj[0]->objMesh.LoadTexture("models/textures/brick.jpg");
	//
	//
	gameobj[1]->objMesh.LoadTexture("models/textures/raygunUVTest.tga");
	//
	gameobj[1]->Translate(0, 3.5f, 0);
	//
	gameobj[2]->Rotate(1.5, 0, 0);
	gameobj[2]->Scale(2.0f);
	gameobj[2]->Translate(4, 3, -4);	
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
			//DestroyBullet(i);
			StickBullet(i);
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

void Game::DeleteBullet(unsigned int i)
{
	bullets.erase(bullets.begin() + bullets[i]->bulletID);
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->bulletID = i;
	}
}

void Game::DestroyBullet(unsigned int i)
{
	rend->RemoveFromRenderer(bullets[i]->bulletModel->rendID);
	rend->RemoveFromLights(bullets[i]->bulletLight->lightID);
	DeleteBullet(i);
}

void Game::StickBullet(unsigned int i)
{
	bullets[i]->bulletModel->SetTag("GameObject");
	bullets[i]->bulletModel->ridgidBody.velocity = glm::vec3(0);
	bullets[i]->bulletModel->applyGrav = false;
	//rend->RemoveFromLights(bullets[i]->bulletLight->lightID);
	gameobj.push_back(bullets[i]->bulletModel);
	DeleteBullet(i);
}

void Game::BulletLightsOn()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->bulletLight->lightID = rend->AddToLights(*bullets[i]->bulletLight);
	}
}

void Game::BulletLightsOff()
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		rend->RemoveFromLights(bullets[i]->bulletLight->lightID);
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
	unsigned int pos = bullets.size();
	bullets.push_back( new Bullet(30, &Engine::GetMesh("Sphere"), rend));
	bullets[pos]->bulletID = pos;
}

