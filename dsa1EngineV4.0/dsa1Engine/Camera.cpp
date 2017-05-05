#include "Camera.h"



Camera::Camera()
{
	t0 = 0;
	t = 0;
	dt = 0;
}

Camera::Camera(GLFWwindow &w)
{
	window = &w;
	t0 = 0;
	t = 0;
	dt = 0;

	sprintSpeed = 3.0f;

	camPos = {0,0,2};
	camRot = {0,0,0};

	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	SetView();
	SetProjection();
}


Camera::~Camera()
{
}

void Camera::SetView()
{
	rotMat = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	camCenter = camPos + (rotMat * glm::vec3(0, 0, -1));
	up = rotMat * glm::vec3(0, 1, 0);

	viewMatrix = glm::lookAt(camPos, camCenter, up);
}

void Camera::SetProjection()
{
	float zoom = 1.0f;
	glfwGetWindowSize(window, &width, &height);

	float fovy = 3.14159f * 0.4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = 0.01f;
	float zFar = 1000.0f;

	ProjectMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}
void Camera::ResetCamera()
{
	camPos = { 0,0,2 };
	camRot = { 0,0,0 };
	SetView();
	SetProjection();
}

void Camera::UpdateCam(bool left, bool right, bool foward, bool backward, bool up, bool down, bool sprint, bool mousePress, bool reset, float dt)
{
	if(mousePress)
	{
		float sens = 0.005f;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		camRot.y -= sens * ((float)x - width * 0.5f);
		camRot.x -= sens * ((float)y - height * 0.5f);
		camRot.x -= glm::clamp(camRot.z, -0.5f*3.145f, 0.5f*3.145f);
		glfwSetCursorPos(window, width * 0.5f, height * 0.5f);
	}
	if(reset)
	{
		ResetCamera();
	}

	camVel = {};
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	
	if(left)
	{
		camVel += R*glm::vec3(-0.001, 0, 0);
	}
	if (right)
	{
		camVel += R*glm::vec3(0.001, 0, 0);
	}
	if (foward)
	{
		camVel += R*glm::vec3(0, 0, -0.001);
	}
	if (backward)
	{
		camVel += R*glm::vec3(0, 0, 0.001);
	}
	if (up)
	{
		camVel += R*glm::vec3(0, 0.001, 0);
	}
	if (down)
	{
		camVel += R*glm::vec3(0, -0.001, 0);
	}

	float speed = 1.0f;
	if(camVel != glm::vec3())
	{
		if(sprint)
		{
			camVel = glm::normalize(camVel) * sprintSpeed;
		}
		else
		{
			camVel = glm::normalize(camVel) * speed;
		}
	}

	camPos += camVel * dt;
}

