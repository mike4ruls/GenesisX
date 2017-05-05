#include "Game.h"

Game::Game(Renderer &r, InputManager &ip)
{
	rend = &r;
	input = &ip;
	light1 = Light("Light1", 1.0f, glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), rend);
	rend->RemoveFromRenderer(light1.sphere->rendID);
	 
	// adds blue ambient to light
	//light1.ambient = {0.0f,0.0f,5.0f,1.0f};
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
	//gameobj.push_back(new GameEntity("too much pizza", "models/teapot.obj", rend));
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
	//gameobj[4]->Rotate(0, 45, 0);
	////gameobj[4]->Scale(0.1f);
	//gameobj[4]->parent = gameobj[3];

	//gameobj[5]->objMesh.specular = { 11,11,11,11 };
	//gameobj[5]->Rotate(0, 1.5, 0);
	//gameobj[5]->Scale(0.1f);
	
}

//bool Game::CanRenderLights(GameEntity obj, Light light)
//{
//	glm::vec3 vecDist = light.lightPos - obj.transform.position;
//	float dist = glm::length(vecDist);
//
//	if(dist < (light.lightRadius + obj.radius))
//	{
//		return true;
//	}
//	return false;
//}

void Game::Update(GLuint program)
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
		light1.myLight.lightRadius -= 0.1f;
	}
	if (input->IsKeyDown(GLFW_KEY_P))
	{
		light1.myLight.lightRadius += 0.1f;
	}
	if (input->IsKeyPressed(GLFW_KEY_TAB))
	{
		rend->ChangeSkyBox();
	}
	if (input->IsKeyDown(GLFW_KEY_0))
	{
		light1.myLight.color = { 1.0f,1.0f,1.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_1))
	{
		light1.myLight.color = { 1.0f,0.0f,0.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_2))
	{
		light1.myLight.color = { 0.0f,1.0f,0.0f,1.0f };
	}
	if (input->IsKeyDown(GLFW_KEY_3))
	{
		light1.myLight.color = { 0.0f,0.0f,1.0f,1.0f };
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
	//(gameobj)[0]->Translate(sin(Engine::time.t)/20.0f,0.0f,0.0f);
	//gameobj[0]->Scale(abs(sin(Engine::time.t))/5.0f);
	//gameobj[0]->Rotate(1.0f*Engine::time.dt, 2.0f*Engine::time.dt, 0.0f);
	//gameobj[1]->Rotate(0.0f, 2.0f*Engine::time.dt, 0.0f);
	
	

	rend->Update(program);
}

void Game::LightingPass(glm::vec3 camPos)
{
	glUniformMatrix4fv(0, 1, GL_FALSE, &light1.sphere->worldPos[0][0]);
	glUniform1f(9, light1.myLight.lightRadius);
	glUniform1f(10, light1.myLight.linear);
	glUniform1f(11, light1.myLight.quadratic);
	glUniform3f(12, light1.myLight.lightPos.x, light1.myLight.lightPos.y, light1.myLight.lightPos.z);
	glUniform3f(13, light1.myLight.color.x, light1.myLight.color.y, light1.myLight.color.z);

	glBindVertexArray(light1.sphere->GetVertArr());
	glDepthMask(GL_FALSE);
	//glDisable(GL_CULL_FACE);
	glDepthFunc(GL_ALWAYS);
	glm::vec3 vecDist = light1.myLight.lightPos - camPos;
	float dist = glm::length(vecDist);
	printf("\n%f", dist);
	if (dist <= light1.myLight.lightRadius)
	{
		//glPolygonMode(GL_FRONT, GL_FILL);
		glCullFace(GL_FRONT);
	}
	glDrawArrays(GL_TRIANGLES,0, light1.sphere->GetCount());
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glCullFace(GL_BACK);
	//glEnable(GL_DEPTH_TEST);
}
