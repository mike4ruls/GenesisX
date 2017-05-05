#include "Engine.h"
#include "Game.h"

Engine::Engine()
{
	shaderM = ShaderManager();
}


Engine::~Engine()
{
}
bool Engine::Init()
{
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindowPtr = glfwCreateWindow(800, 600, "My DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return false; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

	return true;
}
bool Engine::bufferModel()
{
	return true;
}
bool Engine::gameLoop()
{
	Renderer* newRend = new Renderer();
	Game* myGame = new Game(newRend);

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		Engine::Update();
		myGame->Update();

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();
	}

	if (newRend != nullptr) { delete newRend; newRend = nullptr; }
	if (myGame != nullptr) { delete myGame; myGame = nullptr; }
	glfwTerminate();
	return true;
}
bool Engine::useShader()
{
	if(shaderM.LoadShaders("shaders/vShader.glsl","shaders/fShader.glsl"))
	{
		glUseProgram(shaderM.GetProgram());
		return true;
	}
	return false;
}
void Engine::Start()
{
	
}

void Engine::Stop()
{
	
}

void Engine::Update()
{
	time.Update();
	system("cls");
}
Timer Engine::time;
