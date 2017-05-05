#include "Camera.h"



Camera::Camera()
{
	t0 = 0;
	t = 0;
	dt = 0;
	currentMouseClick = false;
}

Camera::Camera(GLFWwindow &w, InputManager &ip)
{
	window = &w;
	input = &ip;

	t0 = 0;
	t = 0;
	dt = 0;

	sprintSpeed = 3.0f;

	camPos = {0,2,15};
	camRot = {0,0,0};

	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	currentMouseClick = false;

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

	glm::mat4 myTrans = glm::translate(camPos);
	glm::mat4 myRot = glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);

	worldPos = myTrans * myRot;

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

void Camera::UpdateCam(float dt)
{
	if (input->IsMouseClick(GLFW_MOUSE_BUTTON_1))
	{
		//printf("Mouse CLICKUUUUUU");
		currentMouseClick = true;
	}
	if (currentMouseClick == true && previousMouseClick == false)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width * 0.5f, height * 0.5f);
	}

	if(currentMouseClick)
	{
		float sens = 0.005f;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		camRot.y -= sens * ((float)x - width * 0.5f);
		camRot.x -= sens * ((float)y - height * 0.5f);
		camRot.x -= glm::clamp(camRot.z, -0.5f*3.145f, 0.5f*3.145f);
		glfwSetCursorPos(window, width * 0.5f, height * 0.5f);
	}
	if (input->IsKeyDown(GLFW_KEY_LEFT_CONTROL) && input->IsKeyDown(GLFW_KEY_C))
	{
		ResetCamera();
	}

	camVel = {};
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	if (input->IsKeyDown(GLFW_KEY_A))
	{
		camVel += R*glm::vec3(-0.001, 0, 0);
	}
	if (input->IsKeyDown(GLFW_KEY_D))
	{
		camVel += R*glm::vec3(0.001, 0, 0);
	}
	if (input->IsKeyDown(GLFW_KEY_W))
	{
		camVel += R*glm::vec3(0, 0, -0.001);
	}
	if (input->IsKeyDown(GLFW_KEY_S))
	{
		camVel += R*glm::vec3(0, 0, 0.001);
	}
	if (input->IsKeyDown(GLFW_KEY_SPACE))
	{
		camVel += R*glm::vec3(0, 0.001, 0);
	}
	if (input->IsKeyDown(GLFW_KEY_X))
	{
		camVel += R*glm::vec3(0, -0.001, 0);
	}



	float speed = 1.0f;
	if(camVel != glm::vec3())
	{
		if (input->IsKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			camVel = glm::normalize(camVel) * sprintSpeed;
		}
		else
		{
			camVel = glm::normalize(camVel) * speed;
		}
	}

	camPos += camVel * dt;
	previousMouseClick = currentMouseClick;
	currentMouseClick = false;
}

