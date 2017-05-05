#pragma once
#include "Timer.h"
#include "ShaderManager.h"
#include "Camera.h"

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
	Camera* mainCam;
	InputManager input;

	static void Start();
	static void Stop();
	static void Update(GLFWwindow* window, int fps);

	static Timer time;
private:
	ShaderManager shaderM;
};

