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
	GameEntity* parent = nullptr;
	Camera* camParent = nullptr;
	GameEntity();
	GameEntity(void *r);
	GameEntity(std::string nm, std::vector<Vertex> &v, std::vector<unsigned int> &i, void *r);
	GameEntity(std::string nm, std::string filename, Mesh::MeshType t, std::string file, void *r);
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
	void CalculateDirections();

	void ApplyForce(glm::vec3 force);
	void ApplyGravity();
	void CalculateFric();
	void UpdateVelocity();
	void FindRadius();

	bool applyGrav;
	float maxSpeed;
	float fricStrength;
	glm::vec3 gravity;

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;
		glm::vec3 forward = {0,0,-1};
		glm::vec3 up = { 0,1,0 };
		glm::vec3 right = { 1,0,0 };
	}transform;
	struct RidgidBody
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 friction;
		float mass;
	}ridgidBody;
	struct Collision
	{
		glm::vec3 originalBoundingBox;
		glm::vec3 boundingBox;
		glm::vec3 center;
		float radius;
	}collider;

private:
	glm::vec3 PREV_FORWARD= { 0,0,1 };
	void* rend;
};

