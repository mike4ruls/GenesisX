#include "Engine.h"
#include "Game.h"

std::map<int, bool> keyIsDown;
std::map<int, bool> keyWasDown;
void MouseClick(GLFWwindow* winPtr, int button, int action, int mods)
{
	keyIsDown[button] = action;
}
void KeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	keyIsDown[key] = action;
}

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

	glfwSetMouseButtonCallback(GLFWwindowPtr, MouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, KeyCallback);
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
		myGame->Update(shaderM.GetProgram());

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);

		// Checking Input
		keyWasDown = keyIsDown;
		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}
		if(keyIsDown[GLFW_MOUSE_BUTTON_1])
		{
			printf("Mouse CLICKUUUUUU");
		}
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

