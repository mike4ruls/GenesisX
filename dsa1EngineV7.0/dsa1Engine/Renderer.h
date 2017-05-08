#pragma once
#include <vector>
#include "ShaderManager.h"
#include "Light.h"
#include <GL\glew.h>
#include "Camera.h"
#include "GameEntity.h"


class Renderer
{
public:
	enum RenderingType {
		Forward,
		Deferred
	}rendType;

	Renderer(Camera *c, ShaderManager& man, int *w, int *h);
	~Renderer();

	void Update();
	void FowardPass(GameEntity *obj);
	void Draw(GameEntity *obj);

	unsigned int AddToRenderer(GameEntity &obj);
	void RemoveFromRenderer(unsigned int pos);

	unsigned int AddToLights(Light &lig);
	void RemoveFromLights(unsigned int pos);

	//sky box methods
	void ChangeSkyBox();
	GLuint loadCubeMap(std::vector<const GLchar*> faces);
	void LoadAllSkyBoxes();
	void DrawSkyBox();

	//skybox variables
	unsigned int currentSky;
	ShaderManager* shaderM;
	Camera* cam;
	GameEntity SkyBoxModel;
	std::vector<GLuint> loadedSkyBoxes;
	GLuint Skybox;

	//deferred rendering methods
	GLuint CreateGeometryBuffer();
	void CreateQuad();

	void SetUpGeometry();
	void GeometryPass(GameEntity &obj);
	void ResetGeometry();

	void SetUpAmbient();
	void AmbientPass();
	void ResetAmbient();

	void SetUpStencil();
	void StencilePass();
	void ResetStencil();

	void SetUpLighting();
	void LightingPass();
	void ResetLighting();

	void BlitInfo();

	//deferred rendering variables
	int* wid;
	int* hei;
	GLuint g_Buffer;
	GLuint colText;
	GLuint normText;
	GLuint worldText;
	GLuint finText;
	GLuint stenText;
	GLuint depthBuffer;
	GLuint vaoQuad;

	//lighting method
	void DeferredLightingSetUp();
	void FowardLightingSetUp();

	//list
	std::vector<GameEntity*> gameObjs;
	std::vector<Light*> lights;
private:

};
