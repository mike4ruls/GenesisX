#include "Renderer.h"



Renderer::Renderer()
{
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
		glBindVertexArray((gameObjs)[i]->GetVertArr());
		glDrawArrays(GL_TRIANGLES, 0, (gameObjs)[i]->GetCount());
		glBindVertexArray(0);
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
