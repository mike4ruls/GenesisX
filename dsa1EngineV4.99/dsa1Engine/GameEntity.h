#pragma once

#include "Mesh.h"
#include "Object.h"
#include "Engine.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
class GameEntity
	:Object
{
public:
	GameEntity();
	GameEntity(void *r);
	GameEntity(std::string nm, std::vector<Vertex> &v, std::vector<unsigned int> &i, void *r);
	GameEntity(std::string nm, std::string filename, void *r);
	GameEntity(std::string nm, Mesh &oM, void *r);
	~GameEntity() override;

	void Update() override;

	void SetWorldPos();
	void ResetGameEntity();

	GLuint GetVertArr();
	unsigned int GetCount();

	void SetTag(std::string tagName);
	std::string GetTag();

	glm::mat4 worldPos;
	
	std::string name;
	unsigned int rendID;
	Mesh objMesh;

	void Translate(glm::vec3 transVec);
	void Translate(float x, float y, float z);
	void Scale(glm::vec3 scaleVec);
	void Scale(float x, float y, float z);
	void Scale(float c);
	void Rotate(glm::vec3 RotVec);
	void Rotate(float x, float y, float z);

	void ApplyForce(glm::vec3 force);
	void ApplyGravity();
	void CalculateFric();
	void UpdateVelocity();

	bool applyGrav;
	float maxSpeed;
	float fricStrength;
	glm::vec3 gravity;

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;
	}transform;
	struct RidgidBody
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 friction;
		float mass;
	}ridgidBody;

private:

	void* rend;
};

