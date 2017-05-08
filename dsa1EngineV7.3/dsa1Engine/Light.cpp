#include "Light.h"
#include "Renderer.h"


Light::Light()
{
}

Light::Light(char* name, float inten,glm::vec3 lightP, glm::vec3 lightD, void* r )
{
	//creating a sphere object
	sphere = new GameEntity(name,"models/sphere.obj", Mesh::SingleMesh,r);
	//setting tag to Light
	sphere->SetTag("Light");

	//loading in data
	myLight.lightPos = lightP;
	myLight.lightDir = lightD;
	myLight.color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	myLight.lightIntensity = inten;

	//calculating a radius based on attenuation variables
	myLight.linear = 0.0;
	myLight.quadratic = 0.1;
	myLight.lightRadius = CalcRadius();
	//printf("%f", myLight.lightRadius);

	//modifying sphere
	sphere->Translate(myLight.lightPos);
	sphere->Scale(myLight.lightRadius);
	lightID = ((Renderer*)r)->AddToLights(*this);
}


Light::~Light()
{
}

void Light::Move(glm::vec3 move)
{
	myLight.lightPos += move;
	sphere->Translate(move);
}
void Light::Move(float x, float y, float z)
{
	myLight.lightPos.x += x;
	myLight.lightPos.y += y;
	myLight.lightPos.z += z;
	sphere->Translate(x,y,z);
}

GLfloat  Light::CalcRadius()
{
	GLfloat radius;
	GLfloat constant = 1.0;
	GLfloat lightMax = std::fmaxf(std::fmaxf(myLight.color.r, myLight.color.g), myLight.color.b);

	radius = (-myLight.linear + std::sqrtf(myLight.linear*myLight.linear - 4 * myLight.quadratic *(constant - (256.0 / 5.0) * lightMax))) / (2 * myLight.quadratic);
	return radius;
}
