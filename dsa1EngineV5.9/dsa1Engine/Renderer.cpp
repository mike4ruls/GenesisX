#include "Renderer.h"
#include <src\SOIL.h>


Renderer::Renderer(Camera *c, ShaderManager& man)
{
	cam = c;
	shaderM = &man;
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	currentSky = 0;

	SkyBoxModel = GameEntity("skybox", "models/box.obj", this);
	RemoveFromRenderer(SkyBoxModel.rendID);
	LoadAllSkyBoxes();


	Skybox = loadedSkyBoxes[currentSky];
}	


Renderer::~Renderer()
{
}

void Renderer::Update(GLuint program)
{
	// clearing the screen
	//gameObjs[5]->camParent = cam;
	for(unsigned int i = 0; i < gameObjs.size(); i++)
	{
		// rendering game object
		float time = Engine::time.t;

		glUniformMatrix4fv(7, 1, GL_FALSE, &(gameObjs)[i]->worldPos[0][0]);
		glUniform1f(10, time);
		//glUniform3f(8, cam->camPos.x, cam->camPos.y, cam->camPos.z);
		glUniform1i(11, gameObjs[i]->objMesh.hasTex);
		//glUniform4f(13, gameObjs[i]->objMesh.specular.x, gameObjs[i]->objMesh.specular.y, gameObjs[i]->objMesh.specular.z, gameObjs[i]->objMesh.specular.w);
		if (gameObjs[i]->objMesh.hasTex)
		{
			glBindTexture(GL_TEXTURE_2D, gameObjs[i]->objMesh.GetTexId());
		}
		if (gameObjs[i]->GetTag() == "Light")
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glBindVertexArray((gameObjs)[i]->GetVertArr());
		glDrawArrays(GL_TRIANGLES, 0, (gameObjs)[i]->GetCount());
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		if (gameObjs[i]->GetTag() == "Light")
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	//DrawSkyBox();
}

unsigned int Renderer::AddToRenderer(GameEntity &obj)
{
	unsigned int pos = gameObjs.size();
	gameObjs.push_back(&obj);

	return pos;
}

void Renderer::RemoveFromRenderer(unsigned int pos)
{
	gameObjs.erase(gameObjs.begin() + pos);
	for(unsigned int i = 0; i < gameObjs.size(); i++)
	{
		(gameObjs)[i]->rendID = i;
	}
}

void Renderer::ChangeSkyBox()
{
	currentSky++;
	if (currentSky >= loadedSkyBoxes.size()) 
	{
		currentSky = 0;
	}
	Skybox = loadedSkyBoxes[currentSky];

}

GLuint Renderer::loadCubeMap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++) {
		image = SOIL_load_image(faces[i],&width,&height,0,SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
		GL_RGB, width, height, 0 , GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void Renderer::LoadAllSkyBoxes()
{
	std::vector<const GLchar*> faces;
	faces.push_back("SkyBox/sunset/right.jpg");
	faces.push_back("SkyBox/sunset/left.jpg");
	faces.push_back("SkyBox/sunset/top.jpg");
	faces.push_back("SkyBox/sunset/bottom.jpg");
	faces.push_back("SkyBox/sunset/back.jpg");
	faces.push_back("SkyBox/sunset/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();

	faces.push_back("SkyBox/space1/right.jpg");
	faces.push_back("SkyBox/space1/left.jpg");
	faces.push_back("SkyBox/space1/top.jpg");
	faces.push_back("SkyBox/space1/bottom.jpg");
	faces.push_back("SkyBox/space1/back.jpg");
	faces.push_back("SkyBox/space1/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();

	faces.push_back("SkyBox/lake/right.jpg");
	faces.push_back("SkyBox/lake/left.jpg");
	faces.push_back("SkyBox/lake/top.jpg");
	faces.push_back("SkyBox/lake/bottom.jpg");
	faces.push_back("SkyBox/lake/back.jpg");
	faces.push_back("SkyBox/lake/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();

	faces.push_back("SkyBox/winter/right.jpg");
	faces.push_back("SkyBox/winter/left.jpg");
	faces.push_back("SkyBox/winter/top.jpg");
	faces.push_back("SkyBox/winter/bottom.jpg");
	faces.push_back("SkyBox/winter/back.jpg");
	faces.push_back("SkyBox/winter/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();

	faces.push_back("SkyBox/lava/right.jpg");
	faces.push_back("SkyBox/lava/left.jpg");
	faces.push_back("SkyBox/lava/top.jpg");
	faces.push_back("SkyBox/lava/bottom.jpg");
	faces.push_back("SkyBox/lava/back.jpg");
	faces.push_back("SkyBox/lava/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();

	faces.push_back("SkyBox/default/right.jpg");
	faces.push_back("SkyBox/default/left.jpg");
	faces.push_back("SkyBox/default/top.jpg");
	faces.push_back("SkyBox/default/bottom.jpg");
	faces.push_back("SkyBox/default/back.jpg");
	faces.push_back("SkyBox/default/front.jpg");
	loadedSkyBoxes.push_back(loadCubeMap(faces));
	faces.clear();
}

void Renderer::DrawSkyBox()
{
	glUseProgram(shaderM->skyProgram);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	glm::mat4 view = glm::mat4(glm::mat3(cam->viewMatrix));
	glUniformMatrix4fv(1, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_FALSE, &cam->ProjectMatrix[0][0]);
	glBindVertexArray(SkyBoxModel.GetVertArr());
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox);
	glDepthFunc(GL_LEQUAL);

	glDrawArrays(GL_TRIANGLES, 0, SkyBoxModel.GetCount());
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	glUseProgram(shaderM->GetProgram());
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void Renderer::LightingPass()
{
}

