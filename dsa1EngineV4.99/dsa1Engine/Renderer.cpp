#include "Renderer.h"



Renderer::Renderer(Camera *c)
{
	cam = c;
	lightPos = glm::vec3(-10,10,2);
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
}	


Renderer::~Renderer()
{
}

void Renderer::Update(GLuint program)
{
	// clearing the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for(unsigned int i = 0; i < gameObjs.size(); i++)
	{
		// rendering game object
		float time = Engine::time.t;
		//GLuint MatrixID = glGetUniformLocation(program, "worldPos");
		//glUseProgram(program);
		glUniformMatrix4fv(4, 1, GL_FALSE, &(gameObjs)[i]->worldPos[0][0]);
		glUniform1f(7, time);
		glUniform3f(8, cam->camPos.x, cam->camPos.y, cam->camPos.z);

		glUniform1i(10, gameObjs[i]->objMesh.hasTex);
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
