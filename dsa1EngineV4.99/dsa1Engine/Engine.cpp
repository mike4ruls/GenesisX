#include "Engine.h"
#include <GL/GLU.h>
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	mainCam = new Camera(*GLFWwindowPtr);
	currentMouseClick = false;
	return true;
}
bool Engine::bufferModel()
{
	return true;
}
bool Engine::gameLoop()
{
	Renderer* newRend = new Renderer(mainCam);
	Game* myGame = new Game(newRend);

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		bool left = false;
		bool right = false;
		bool foward = false;
		bool backward = false;
		bool up = false;
		bool down = false;
		bool sprint = false;
		bool resetCam = false;
		bool forceOn = false;
		bool gravOn = false;
		
		if (keyIsDown[GLFW_KEY_LEFT] || keyIsDown[GLFW_KEY_A])
		{
			left = true;
		}
		if (keyIsDown[GLFW_KEY_RIGHT] || keyIsDown[GLFW_KEY_D])
		{
			right = true;
		}
		if (keyIsDown[GLFW_KEY_UP] || keyIsDown[GLFW_KEY_W])
		{
			foward = true;
		}
		if (keyIsDown[GLFW_KEY_DOWN] || keyIsDown[GLFW_KEY_S])
		{
			backward = true;
		}
		if (keyIsDown[GLFW_KEY_SPACE])
		{
			up = true;
		}
		if (keyIsDown[GLFW_KEY_X])
		{
			down = true;
		}
		if (keyIsDown[GLFW_KEY_LEFT_SHIFT])
		{
			sprint = true;
		}
		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}
		if(keyIsDown[GLFW_KEY_LEFT_CONTROL] && keyIsDown[GLFW_KEY_C])
		{
			resetCam = true;
		}
		if (keyIsDown[GLFW_MOUSE_BUTTON_1])
		{
			printf("Mouse CLICKUUUUUU");
			currentMouseClick = true;
		}
		if(currentMouseClick == true && previousMouseClick == false)
		{
			int width, height;
			glfwGetWindowSize(GLFWwindowPtr, &width, &height);
			glfwSetCursorPos(GLFWwindowPtr, width * 0.5f, height * 0.5f);
		}
		if (keyIsDown[GLFW_KEY_N])
		{
			forceOn = true;
		}
		if (keyIsDown[GLFW_KEY_G])
		{
			gravOn = true;
		}

		mainCam->SetProjection();
		mainCam->SetView();
		mainCam->UpdateCam(left, right, foward, backward, up, down, sprint, currentMouseClick, resetCam, time.dt);

		glUniformMatrix4fv(5, 1, GL_FALSE, &mainCam->viewMatrix[0][0]);
		glUniformMatrix4fv(6, 1, GL_FALSE, &mainCam->ProjectMatrix[0][0]);

		Engine::Update();
		myGame->Update(shaderM.GetProgram(), forceOn, gravOn);

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);

		// Checking Input
		keyWasDown = keyIsDown;
		previousMouseClick = currentMouseClick;
		currentMouseClick = false;
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

