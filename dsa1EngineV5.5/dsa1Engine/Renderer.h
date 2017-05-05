#pragma once
#include <vector>
#include "ShaderManager.h"
#include <GL\glew.h>
#include "Camera.h"
#include "GameEntity.h"


class Renderer
{
public:
	Renderer(Camera *c, ShaderManager& man);
	~Renderer();

	void Update(GLuint program);
	unsigned int AddToRenderer(GameEntity &obj);
	void RemoveFromRenderer(unsigned int pos);
	void ChangeSkyBox();
	GLuint loadCubeMap(std::vector<const GLchar*> faces);
	void LoadAllSkyBoxes();

	int currentSky;
	ShaderManager* shaderM;
	Camera* cam;
	glm::vec3 lightPos;
	GameEntity SkyBoxModel;
	std::vector<GLuint> loadedSkyBoxes;
	GLuint Skybox;

	std::vector<GameEntity*> gameObjs;
private:

};

