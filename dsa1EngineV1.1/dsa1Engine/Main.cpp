#include <iostream>
#include <vector>
#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

int main()
{
	if (glfwInit() == GL_FALSE) return -1;

	GLFWwindow* GLFWwindowPtr = glfwCreateWindow(800, 600, "My DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return -1; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }
	std::vector<glm::vec3> verts = { {-0.5,-0.5,0.0},
									{-0.5,0.5,0.0},
									{0.5,0.5,0.0},
									{0.5,-0.5,0.0} };
	std::vector<unsigned int> ind = {0,1,2,0,2,3 };
	unsigned int count = ind.size();

	std::vector<glm::vec3> vertBufData(count);

	for(unsigned int i = 0; i < count; i++)
	{
		vertBufData[i] = verts[ind[i]];
	}

	//initailizing buffer we want to use
	GLuint vertArr;
	GLuint vertBuf;

	// generating buffer and storing their addresses to out init variables
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	// placing our buffer on the machine
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	// binding our data to the buffer on the machine, know they wont change in size not matter what
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec3)*count,
		&vertBufData[0],
		GL_STATIC_DRAW);

	// letting the computer know how the buffer is structured
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, // the index
						3, // number of components to expect(x,y,z)
						GL_FLOAT, // Type of data
						GL_FALSE, // should we normalize the data
						sizeof(glm::vec3), // stride
						0); // the offset 
	// unbind after all the settings are changed and correct
	glBindVertexArray(0);

	// changing screen backgroung color when we clear the screen
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	

	while(!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// clearing the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// rendering game object
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, count);
		glBindVertexArray(0);

		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}