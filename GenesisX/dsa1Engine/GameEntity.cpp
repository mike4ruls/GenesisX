#include "GameEntity.h"
#include "Renderer.h"



GameEntity::GameEntity()
{
}

GameEntity::GameEntity(void *r)
	:Object()
{
	name = "";
	tag = "GameObject";
	objMesh = Mesh();
	rend = r;
	rendID = ((Renderer*)rend)->AddToRenderer(*this);
	ResetGameEntity();
}
GameEntity::GameEntity(std::string nm, Mesh &oM, void *r)
	:Object()
{
	name = nm;
	tag = "GameObject";
	objMesh = oM;
	rend = r;
	rendID = ((Renderer*)rend)->AddToRenderer(*this);
	ResetGameEntity();
}
GameEntity::GameEntity(std::string nm, std::vector<Vertex> &v, std::vector<unsigned int> &i, void *r)
	:Object()
{
	name = nm;
	tag = "GameObject";
	objMesh = Mesh(v, i);
	rend = r;
	rendID = ((Renderer*)rend)->AddToRenderer(*this);
	ResetGameEntity();
}

GameEntity::GameEntity(std::string nm, std::string filename, Mesh::MeshType t, std::string file,void * r)
{
	name = nm;
	tag = "GameObject";
	objMesh = Mesh(filename, t, file);
	rend = r;
	rendID = ((Renderer*)rend)->AddToRenderer(*this);
	ResetGameEntity();
}

GameEntity::~GameEntity()
{
	//((Renderer*)rend)->RemoveFromRenderer(rendID);
}
void GameEntity::Update()
{
	//printf("updating at time %f\n", Engine::time.t);
	//printf("Rendering %s", &tag[0]);
	if(applyGrav)
	{
		ApplyGravity();
	}
	//CalculateFric();
	UpdateVelocity();
	if(transform.forward != PREV_FORWARD)
	{
		CalculateDirections();
	}
}
void GameEntity::SetWorldPos()
{
	glm::mat4 myTrans = glm::translate(transform.position);
	glm::mat4 myScale = glm::scale(transform.scale);
	glm::mat4 myRot = glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	worldPos = myTrans * myRot * myScale;

	if (parent != nullptr) {
		worldPos = parent->worldPos * worldPos;
	}
	if (camParent != nullptr) {
		worldPos = camParent->viewMatrix * worldPos;
	}
}
void GameEntity::ResetGameEntity()
{
	worldPos = glm::mat4(1.0f);
	applyGrav = false;
	maxSpeed = 0.3f;
	fricStrength = 0.1f;
	gravity = {0,-1.0f,0};

	transform.position = {0.0f,0.0f,0.0f};
	transform.scale = { 1.0f,1.0f,1.0f};
	transform.rotation = { 0.0f,0.0f,0.0f};

	ridgidBody.velocity = { 0.0f,0.0f,0.0f };
	ridgidBody.acceleration = { 0.0f,0.0f,0.0f };
	ridgidBody.friction = { 0.0f,0.0f,0.0f };
	ridgidBody.mass = 1.0f;

	FindRadius();
	SetWorldPos();
}
GLuint GameEntity::GetVertArr()
{
	return objMesh.vertArr;
}

unsigned int GameEntity::GetCount()
{
	return objMesh.count;
}

void GameEntity::SetTag(std::string tagName)
{
	tag = tagName;
}

std::string GameEntity::GetTag()
{
	return tag;
}
void GameEntity::FindRadius()
{
	float largestX = 0;
	float largestY = 0;
	float largestZ = 0;
	for(unsigned int i = 0; i< objMesh.verts.size();i++)
	{
		glm::vec3 pos = objMesh.verts[i].pos;
		float x = glm::abs(pos.x);
		float y = glm::abs(pos.y);
		float z = glm::abs(pos.z);
		if(x > largestX)
		{
			largestX = x;
		}
		if (y > largestY)
		{
			largestY = y;
		}
		if (z > largestZ)
		{
			largestZ = z;
		}
	}
	if(largestX == 0)
	{
		largestX = 0.5f;
	}
	if (largestY == 0)
	{
		largestY = 0.5f;
	}
	if (largestZ == 0)
	{
		largestZ = 0.5f;
	}

	collider.originalBoundingBox = glm::vec3(largestX,largestY,largestZ);
	collider.boundingBox = collider.originalBoundingBox * transform.scale;
	collider.radius = glm::distance(glm::vec3( 0,0,0 ),collider.boundingBox);
}

#pragma region Tranform Methods

void GameEntity::Translate(glm::vec3 transVec)
{
	transform.position.x += transVec.x;
	transform.position.y += transVec.y;
	transform.position.z += transVec.z;

	SetWorldPos();
}

void GameEntity::Translate(float x, float y, float z)
{
	transform.position.x += x;
	transform.position.y += y;
	transform.position.z += z;

	SetWorldPos();
}

void GameEntity::Scale(glm::vec3 scaleVec)
{
	transform.scale.x = scaleVec.x;
	transform.scale.y = scaleVec.y;
	transform.scale.z = scaleVec.z;

	collider.boundingBox = collider.originalBoundingBox * transform.scale;
	collider.radius = glm::distance({ 0,0,0 }, collider.boundingBox);
	SetWorldPos();
}

void GameEntity::Scale(float x, float y, float z)
{
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;

	collider.boundingBox = collider.originalBoundingBox * transform.scale;
	collider.radius = glm::distance({ 0,0,0 }, collider.boundingBox);
	SetWorldPos();
}

void GameEntity::Scale(float c)
{
	transform.scale.x = c;
	transform.scale.y = c;
	transform.scale.z = c;

	collider.boundingBox = collider.originalBoundingBox * transform.scale;
	collider.radius = glm::distance({ 0,0,0 }, collider.boundingBox);
	SetWorldPos();
}

void GameEntity::Rotate(glm::vec3 RotVec)
{
	transform.rotation.x += RotVec.x;
	transform.rotation.y += RotVec.y;
	transform.rotation.z += RotVec.z;

	SetWorldPos();
}

void GameEntity::Rotate(float x, float y, float z)
{
	transform.rotation.x += x;
	transform.rotation.y += y;
	transform.rotation.z += z;

	SetWorldPos();
}
void GameEntity::CalculateDirections()
{
	transform.up = glm::cross(glm::cross(transform.forward, glm::vec3(0, 1, 0)), transform.forward);
	transform.right = glm::cross(transform.up, transform.forward);

	PREV_FORWARD = transform.forward;
}
#pragma endregion

#pragma region Ridgid Body Methods

void GameEntity::ApplyForce(glm::vec3 force)
{
	ridgidBody.acceleration += force / ridgidBody.mass;
}

void GameEntity::ApplyGravity()
{
	ridgidBody.acceleration += gravity * ridgidBody.mass;
}

void GameEntity::CalculateFric()
{
	if (glm::length(ridgidBody.velocity) <= 0.001f)
	{
		//ridgidBody.velocity = { 0.0f,0.0f,0.0f };
		ridgidBody.friction = { 0.0f,0.0f,0.0f };
		return;
	}

	ridgidBody.friction = ridgidBody.velocity * -1.0f;
	ridgidBody.friction = glm::normalize(ridgidBody.friction);
	ridgidBody.friction *= fricStrength;
	ApplyForce(ridgidBody.friction);
}

void GameEntity::UpdateVelocity()
{
	
	ridgidBody.velocity += ridgidBody.acceleration * Engine::time.dt;
	ridgidBody.velocity = glm::clamp(ridgidBody.velocity, -1.0f, maxSpeed);
	ridgidBody.acceleration = { 0.0f,0.0f,0.0f };

	if (glm::length(ridgidBody.velocity) <= 0.001f && glm::length(ridgidBody.velocity) >= -0.001f)
	{
		ridgidBody.velocity = { 0.0f,0.0f,0.0f };
	}
	Translate(ridgidBody.velocity);
}
#pragma endregion
