#pragma once
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
class Camera
{
public:
	Camera();
	Camera(GLFWwindow &window);
	~Camera();

	glm::vec3 camPos;
	glm::vec3 camRot;
	glm::vec3 camCenter;
	glm::vec3 camDir;
	glm::vec3 camVel;
	glm::vec3 up;
	glm::mat3 rotMat;

	glm::mat4 viewMatrix;
	glm::mat4 ProjectMatrix;

	GLFWwindow* window;

	int width;
	int height;
	float sprintSpeed;

	void SetView();
	void SetProjection();
	void ResetCamera();
	void UpdateCam(bool left, bool right, bool foward, bool backward, bool up, bool down, bool sprint, bool mousePress, bool reset, float dt);


private:
	float t0;
	float t;
	float dt;
};

