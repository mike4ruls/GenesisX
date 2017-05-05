#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "Game.h"
int main()
{
	// Creating Window
	if (glfwInit() == GL_FALSE) return -1;

	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "My DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return -1; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }

	Engine::Start();
	Game* myGame = new Game();

	while(!glfwWindowShouldClose(GLFWwindowPtr))
	{
		Engine::Update();
		myGame->Update();

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();
	}
	delete myGame;
	Engine::Stop();
	glfwTerminate();
	return 0;
}