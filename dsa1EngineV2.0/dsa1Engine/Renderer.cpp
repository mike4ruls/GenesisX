#include "Renderer.h"



Renderer::Renderer()
{
}
Renderer::Renderer(std::vector<GameEntity> &go)
{
	gameObjs = go;
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
}


Renderer::~Renderer()
{
}

void Renderer::Update()
{
	// clearing the screen
	glClear(GL_COLOR_BUFFER_BIT);

	for(unsigned int i = 0; i < gameObjs.size(); i++)
	{
		// rendering game object
		glBindVertexArray(gameObjs[i].GetVertArr());
		glDrawArrays(GL_TRIANGLES, 0, gameObjs[i].GetCount());
		glBindVertexArray(0);
	}
	
}
