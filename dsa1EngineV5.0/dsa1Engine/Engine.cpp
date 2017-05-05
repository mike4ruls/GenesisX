#include "Engine.h"
#include <GL/GLU.h>
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
	Renderer* newRend = new Renderer(mainCam);
	Game* myGame = new Game(*newRend, input);

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		if (input.IsKeyDown(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}

		mainCam->SetProjection();
		mainCam->SetView();
		mainCam->UpdateCam(time.dt);
		//input.Update();

		glUniformMatrix4fv(5, 1, GL_FALSE, &mainCam->viewMatrix[0][0]);
		glUniformMatrix4fv(6, 1, GL_FALSE, &mainCam->ProjectMatrix[0][0]);\

		const char* titleName = "Michael Ray DSA1 Engine Fps: " + (int)Engine::time.fps;
		Engine::Update(GLFWwindowPtr, (int)Engine::time.fps);
		myGame->Update(shaderM.GetProgram());

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

void Engine::Update(GLFWwindow* window, int fps)
{
	time.Update();
	system("cls");
	glfwSetWindowTitle(window, "Michael Ray DSA1 Engine Fps: " + fps);
}
Timer Engine::time;

