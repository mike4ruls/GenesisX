#pragma once
#include "Timer.h"
#include "ShaderManager.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

class Engine
{
public:
	Engine();
	~Engine();

	// What does static do?
	bool Init();
	bool bufferModel();
	bool gameLoop();
	bool useShader();

	GLFWwindow* GLFWwindowPtr;

	static void Start();
	static void Stop();
	static void Update();

	static Timer time;
private:
	ShaderManager shaderM;
};

