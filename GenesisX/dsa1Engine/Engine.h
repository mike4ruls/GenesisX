#pragma once
#include "Timer.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Mesh.h"
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
	static float Random();

	static bool LoadMesh(std::string meshName, std::string fileName, Mesh::MeshType mT, std::string filePath);
	static Mesh GetMesh(std::string name);

	static std::map <std::string, Mesh> MeshDictionary;

	static Timer time;

private:
	
};

