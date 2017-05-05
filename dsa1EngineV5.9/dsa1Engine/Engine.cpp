#include "Engine.h"
#include <GL/GLU.h>
#include "Game.h"

Engine::Engine()
{
	shaderM = new ShaderManager();
}


Engine::~Engine()
{
}
bool Engine::Init()
{
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Michael Ray DSA1 Engine", NULL, NULL);
	if (GLFWwindowPtr != nullptr)glfwMakeContextCurrent(GLFWwindowPtr);
	else { glfwTerminate(); return false; }

	if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

	input = InputManager(*GLFWwindowPtr);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	mainCam = new Camera(*GLFWwindowPtr, input);
	return true;
}
bool Engine::bufferModel()
{
	return true;
}
bool Engine::gameLoop()
{
	Renderer* newRend = new Renderer(mainCam, *shaderM);
	Game* myGame = new Game(*newRend, input);
	glfwGetWindowSize(GLFWwindowPtr, &width, &height);
	g_Buffer = CreateGeometryBuffer();

	GLfloat quadVertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	GLuint vboQuad;
	glGenBuffers(1, &vboQuad);

	GLuint vaoQuad;
	glGenVertexArrays(1, &vaoQuad);

	glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindVertexArray(vaoQuad);
	glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
	
	//GLint posAttrib = glGetAttribLocation(shaderM->lightProgram, "position");
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	//GLint texAttrib = glGetAttribLocation(shaderM->lightProgram, "texcoord");
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		if (input.IsKeyDown(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}

		mainCam->SetProjection();
		mainCam->SetView();
		mainCam->UpdateCam(time.dt);
		//input.Update();
		
		glBindFramebuffer(GL_FRAMEBUFFER, g_Buffer);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shaderM->geoProgram);
		glUniformMatrix4fv(8, 1, GL_FALSE, &mainCam->viewMatrix[0][0]);
		glUniformMatrix4fv(9, 1, GL_FALSE, &mainCam->ProjectMatrix[0][0]);
		myGame->Update(shaderM->geoProgram);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glUseProgram(shaderM->lightProgram);
		LightinPass();
		myGame->LightingPass();
		glBindVertexArray(vaoQuad);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, g_Buffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

		newRend->DrawSkyBox();
		
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		//GLuint piz = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		//GLuint za = GL_FRAMEBUFFER_COMPLETE;
		//if (piz != za) { return false; }
		

		std::string titleName = "Michael Ray DSA1 Engine Fps: ";
		titleName.push_back((int)(15));
		glfwSetWindowTitle(GLFWwindowPtr, &titleName[0]);
		Engine::Update(GLFWwindowPtr, titleName);


		//glReadPixels();
		// swap chain
		glfwSwapBuffers(GLFWwindowPtr);

		// Checking Input	
		glfwPollEvents();
	}

	if (newRend != nullptr) { delete newRend; newRend = nullptr; }
	if (myGame != nullptr) { delete myGame; myGame = nullptr; }
	glfwTerminate();
	return true;
}
bool Engine::useShader()
{
	if(shaderM->LoadShaders("shaders/vShader.glsl","shaders/fShader.glsl", shaderM->regProgram))
	{
	
	//return true;
	}
	if (shaderM->LoadShaders("shaders/skyBoxVShader.glsl", "shaders/skyBoxPShader.glsl", shaderM->skyProgram))
	{
		//return true;
	}
	if (shaderM->LoadShaders("shaders/lightingVShader.glsl", "shaders/lightingShader.glsl", shaderM->lightProgram))
	{
		int i =0;
	}
	if (shaderM->LoadShaders("shaders/geometryVShader.glsl", "shaders/geometryShader.glsl", shaderM->geoProgram))
	{
		glUseProgram(shaderM->GetProgram());
		return true;
	}
	return false;
}
GLuint Engine::CreateGeometryBuffer()
{
	// getting the windows width and height

	GLuint piz = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GLuint za = GL_FRAMEBUFFER_COMPLETE;

	// create a new render target to render to
	GLuint newFrameBuffer;
	glGenFramebuffers(1, &newFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, newFrameBuffer);


	// create a new texture to render my color to
	glGenTextures(1, &colText);
	glBindTexture(GL_TEXTURE_2D, colText);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,width,height,0, GL_RGB,GL_UNSIGNED_BYTE,0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// create a new texture to render my normals to
	glGenTextures(1, &normText);
	glBindTexture(GL_TEXTURE_2D, normText);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// create a new texture to render my world positions to
	glGenTextures(1, &worldText);
	glBindTexture(GL_TEXTURE_2D, worldText);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// create a depth buffer
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

	// attaching buffers to render target
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colText, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, normText, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, worldText, 0);

	GLenum DrawBuffer[3] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, DrawBuffer);
	piz = glCheckFramebufferStatus(GL_FRAMEBUFFER);
 	if (piz != za) { return false; }

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return newFrameBuffer;
}
void Engine::LightinPass()
{
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normText);
	glUniform1i(8, 1);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, worldText);
	glUniform1i(9, 2);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colText);
	glUniform1i(7, 0);

	glUniform4f(0, mainCam->camPos.x, mainCam->camPos.y, mainCam->camPos.z, 1.0f);
	//rend.LightingPass();


	
}
void Engine::Start()
{
	
}

void Engine::Stop()
{
	
}

void Engine::Update(GLFWwindow* window, std::string title)
{
	time.Update();
	system("cls");
	//glfwSetWindowTitle(window, &title[0]);
}
Timer Engine::time;

