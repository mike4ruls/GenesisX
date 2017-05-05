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

	// What does static do?
	bool Init();
	bool bufferModel();
	bool gameLoop();
	bool useShader();
	GLuint CreateGeometryBuffer();
	void AmbientPass();
	void StencilePass();
	void LightingPass();


	int width;
	int height;
	GLFWwindow* GLFWwindowPtr;
	Camera* mainCam;
	GLuint g_Buffer;
	GLuint colText;
	GLuint normText;
	GLuint worldText;
	GLuint finText;
	GLuint stenText;
	GLuint depthBuffer;
	GLuint vaoQuad;
	InputManager input;

	static void Start();
	static void Stop();
	static void Update(GLFWwindow* window, std::string title);

	static Timer time;
	ShaderManager* shaderM;
private:
	
};

