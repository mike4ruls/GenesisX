#include <iostream>
#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

int main()
{
	if(glfwInit() == GL_FALSE) return -1;

	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "My DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate; return -1; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }

	while(!glfwWindowShouldClose(GLFWwindowPtr))
	{
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}