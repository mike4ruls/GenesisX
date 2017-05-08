#include "Bullet.h"
#include "Renderer.h"



Bullet::Bullet()
{
}

Bullet::Bullet(float s, std::string file, void* r)
{
	speed = s;
	glm::vec3 camPos = ((Renderer*)r)->cam->camCenter;
	glm::vec3 foward = ((Renderer*)r)->cam->foward;
	glm::vec4 color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);

	bulletTime = 0.0f;
	bulletLifeSpan = 3.0f;

	bulletModel = new GameEntity("my bullet",file,Mesh::SingleMesh, r);
	bulletLight = new Light("my bullet light", 1.0, camPos, glm::vec3(0, 0, 0), r);
	((Renderer*)r)->RemoveFromRenderer(bulletLight->sphere->rendID);
	bulletLight->myLight.color = color;

	bulletModel->SetTag("Bullet");
	bulletModel->Translate(camPos);
	//bulletModel->ridgidBody.mass = 0.5f;
	bulletModel->objMesh.color = color;
	//bulletModel->applyGrav = true;
	bulletModel->ApplyForce(foward * (glm::vec3(1)*speed));
}
Bullet::Bullet(float s, Mesh* myMesh, void* r)
{
	speed = s;
	glm::vec3 camPos = ((Renderer*)r)->cam->camCenter;
	glm::vec3 foward = ((Renderer*)r)->cam->foward;
	glm::vec4 color = glm::vec4(glm::normalize(glm::vec3(Engine::Random(), Engine::Random(), Engine::Random())), 1);

	bulletTime = 0.0f;
	bulletLifeSpan = 3.0f;

	bulletModel = new GameEntity("my bullet", *myMesh, r);
	bulletLight = new Light("my bullet light", 1.0, camPos, glm::vec3(0, 0, 0), r);
	((Renderer*)r)->RemoveFromRenderer(bulletLight->sphere->rendID);
	bulletLight->myLight.color = color;

	bulletModel->SetTag("Bullet");
	bulletModel->Translate(camPos + foward);
	//bulletModel->ridgidBody.mass = 0.5f;
	bulletModel->objMesh.color = color;
	//bulletModel->applyGrav = true;
	bulletModel->ApplyForce(foward * (glm::vec3(1)*speed));
}


Bullet::~Bullet()
{
	if (bulletModel != nullptr) { delete bulletModel;  bulletModel = nullptr; }
	if (bulletLight != nullptr) { delete bulletLight;  bulletLight = nullptr; }
}

void Bullet::Update()
{
	bulletModel->Update();

	printf("x: %.3f, y: %.3f, z: %.3f\n", bulletModel->ridgidBody.velocity.x, bulletModel->ridgidBody.velocity.y, bulletModel->ridgidBody.velocity.z);

	bulletLight->Move(bulletModel->ridgidBody.velocity);

	bulletTime += Engine::time.dt;

	if (bulletTime > bulletLifeSpan) {
		destroyBullet = true;
	}
}
