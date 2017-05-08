#pragma once
#include "Timer.h"
#include "Camera.h"
#include "ShaderManager.h"
#include <glm\glm.hpp>

class Engine
{
public:
	Engine();
	~Engine();

	//setup engine methods
	bool Init();
	bool bufferModel();
	bool gameLoop();
	bool useShader();

	//engine variables
	int width;
	int height;
	GLFWwindow* GLFWwindowPtr;
	Camera* mainCam;
	InputManager input;
	ShaderManager* shaderM;

	//static stuff
	static void Start();
	static void Stop();
	static void Update(GLFWwindow* window, std::string title);

	static Timer time;

private:
	
};

