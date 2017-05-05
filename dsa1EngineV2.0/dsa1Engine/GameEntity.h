#pragma once
#include "Mesh.h"
#include "Object.h"
#include "Engine.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
class GameEntity
	:Object
{
public:
	GameEntity();
	GameEntity(std::string nm, std::vector<Vertex> &v, std::vector<unsigned int> &i);
	GameEntity(std::string nm, Mesh &oM);
	~GameEntity() override;

	void Update() override;

	void SetWorldPos();
	void ResetGameEntity();

	GLuint GetVertArr();
	unsigned int GetCount();

	glm::mat4x4 worldPos;
	
	std::string name;
	Mesh objMesh;

	void Translate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Scale(float c);
	void Rotate(float x, float y, float z);

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;


};

