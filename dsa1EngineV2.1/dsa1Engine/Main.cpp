#include "Game.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
int main()
{
	// Creating Window
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "My DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return false; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }
	Renderer* newRend = new Renderer();
	Game* myGame = new Game(newRend);
	Engine::Start();

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		Engine::Update();
		myGame->Update();

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();
	}

	glfwTerminate();
	if (newRend != nullptr) { delete newRend; newRend = nullptr; }
	if (myGame != nullptr) { delete myGame; myGame = nullptr; }
	Engine::Stop();
	return 0;
}
