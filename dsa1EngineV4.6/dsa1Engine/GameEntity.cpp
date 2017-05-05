#include "GameEntity.h"
#include "Renderer.h"



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

GameEntity::GameEntity(std::string nm, std::string filename, void * r)
{
	name = nm;
	tag = "GameObject";
	objMesh = Mesh(filename);
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
	printf("updating at time %f\n", Engine::time.t);
	printf("Rendering %s", &tag[0]);
	
}
void GameEntity::SetWorldPos()
{
	glm::mat4 myTrans = glm::translate(position);
	glm::mat4 myScale = glm::scale(scale);
	glm::mat4 myRot = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

	worldPos = myTrans * myRot * myScale;
}
void GameEntity::ResetGameEntity()
{
	worldPos = glm::mat4(1.0f);

	position = {0.0f,0.0f,0.0f};
	scale = { 1.0f,1.0f,1.0f};
	rotation = { 0.0f,0.0f,0.0f};

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

void GameEntity::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	SetWorldPos();
}

void GameEntity::Scale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;

	SetWorldPos();
}

void GameEntity::Scale(float c)
{
	scale.x = c;
	scale.y = c;
	scale.z = c;

	SetWorldPos();
}

void GameEntity::Rotate(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;

	SetWorldPos();
}
