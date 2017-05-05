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

		//drawing to 3 textures
		GLenum DrawBuffer[3] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, DrawBuffer);

		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glUseProgram(shaderM->geoProgram);
		glUniformMatrix4fv(8, 1, GL_FALSE, &mainCam->viewMatrix[0][0]);
		glUniformMatrix4fv(9, 1, GL_FALSE, &mainCam->ProjectMatrix[0][0]);
		myGame->Update(shaderM->geoProgram);
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);

		//clearing final texture
		glDrawBuffer(GL_COLOR_ATTACHMENT3);
		glClear(GL_COLOR_BUFFER_BIT);

		AmbientPass();

		LightingPass();
		myGame->LightingPass(mainCam->camPos);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, g_Buffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glReadBuffer(GL_COLOR_ATTACHMENT3);
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	if(!shaderM->LoadShaders("shaders/RegularShading/vShader.glsl","shaders/RegularShading/fShader.glsl", shaderM->regProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/SkyBoxShading/skyBoxVShader.glsl", "shaders/SkyBoxShading/skyBoxPShader.glsl", shaderM->skyProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/geometryVShader.glsl", "shaders/DeferredShading/geometryPShader.glsl", shaderM->geoProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/nullV.glsl", "shaders/DeferredShading/nullP.glsl", shaderM->nulProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/ambientVShader.glsl", "shaders/DeferredShading/ambientPShader.glsl", shaderM->ambProgram))
	{
		return false;
	}
	if (!shaderM->LoadShaders("shaders/DeferredShading/lightVShader.glsl", "shaders/DeferredShading/lightPShader.glsl", shaderM->ligProgram))
	{
		return false;
	}
	glUseProgram(shaderM->GetProgram());
	return true;
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// create a new texture to render my world positions to
	glGenTextures(1, &worldText);
	glBindTexture(GL_TEXTURE_2D, worldText);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// create a depth buffer
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

	// create a stencil buffer
	glGenTextures(1, &stenText);
	glBindTexture(GL_TEXTURE_2D, stenText);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);

	//// create a new texture to render my final texture
	glGenTextures(1, &finText);
	glBindTexture(GL_TEXTURE_2D, finText);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_FLOAT, NULL);

	// attaching buffers to render target
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colText, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, normText, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, worldText, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stenText, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, finText, 0);

	GLenum DrawBuffer[3] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, DrawBuffer);
	piz = glCheckFramebufferStatus(GL_FRAMEBUFFER);
 	if (piz != za) { return false; }

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return newFrameBuffer;
}
void Engine::AmbientPass()
{
	glUseProgram(shaderM->ambProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colText);
	glUniform1i(2, 0);

	//glUniform4f(0, mainCam->camPos.x, mainCam->camPos.y, mainCam->camPos.z, 1.0f);
	glBindVertexArray(vaoQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	//rend.LightingPass();	
}
void Engine::StencilePass()
{
	glUseProgram(shaderM->nulProgram);
	glDrawBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS,0,0);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);
}
void Engine::LightingPass()
{
	glUseProgram(shaderM->ligProgram);
	//glStencilFunc(GL_NOTEQUAL, 0 , 0xFF);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE,GL_ONE);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glDisable(GL_CULL_FACE);

	glUniformMatrix4fv(1, 1, GL_FALSE, &mainCam->ProjectMatrix[0][0]);
	glUniformMatrix4fv(2, 1, GL_FALSE, &mainCam->viewMatrix[0][0]);
	glUniform1f(7, width);
	glUniform1f(8, height);
	glUniform3f(14, mainCam->camPos.x, mainCam->camPos.y, mainCam->camPos.z);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normText);
	glUniform1i(16, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, worldText);
	glUniform1i(17, 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colText);
	//glBindTexture(GL_TEXTURE_2D, 4);
	glUniform1i(15, 0);
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
	//system("cls");
	//glfwSetWindowTitle(window, &title[0]);
}
Timer Engine::time;

