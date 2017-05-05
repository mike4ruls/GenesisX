#include "Engine.h"
#include <GL/GLU.h>
#include "Game.h"

Engine::Engine()
{
	shaderM = new ShaderManager();
}


Engine::~Engine()
{
}
bool Engine::Init()
{
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Michael Ray DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return false; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

	input = InputManager(*GLFWwindowPtr);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	mainCam = new Camera(*GLFWwindowPtr, input);
	return true;
}
bool Engine::bufferModel()
{
	return true;
}
bool Engine::gameLoop()
{
	glfwGetWindowSize(GLFWwindowPtr, &width, &height);
	Renderer* newRend = new Renderer(mainCam, *shaderM, &width, &height);
	Game* myGame = new Game(*newRend, input);

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		if (input.IsKeyDown(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}
		//updating camera
		mainCam->SetProjection();
		mainCam->SetView();
		mainCam->UpdateCam(time.dt);

		//updating models
		myGame->Update();

		//rendering models
		newRend->Update();

		//updating title
		std::string titleName = "Michael Ray DSA1 Engine Fps: ";
		Engine::Update(GLFWwindowPtr, titleName);

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);

		// Checking Input	
		glfwPollEvents();
	}

	if (newRend != nullptr) { delete newRend; newRend = nullptr; }
	if (myGame != nullptr) { delete myGame; myGame = nullptr; }
	glfwTerminate();
	return true;
}
bool Engine::useShader()
{
	if(!shaderM->LoadShaders("shaders/RegularShading/vShader.glsl","shaders/RegularShading/fShader.glsl", shaderM->regProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/SkyBoxShading/skyBoxVShader.glsl", "shaders/SkyBoxShading/skyBoxPShader.glsl", shaderM->skyProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/geometryVShader.glsl", "shaders/DeferredShading/geometryPShader.glsl", shaderM->geoProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/nullV.glsl", "shaders/DeferredShading/nullP.glsl", shaderM->nulProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/ambientVShader.glsl", "shaders/DeferredShading/ambientPShader.glsl", shaderM->ambProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/lightVShader.glsl", "shaders/DeferredShading/lightPShader.glsl", shaderM->ligProgram))
	{
		return false;
	}
	glUseProgram(shaderM->GetProgram());
	return true;
}
void Engine::Start()
{
	
}

void Engine::Stop()
{
	
}

void Engine::Update(GLFWwindow* window, std::string title)
{
	time.Update();
}
Timer Engine::time;

