#include "Engine.h"



Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Start()
{
}

void Engine::Stop()
{
}

void Engine::Update()
{
	time.Update();
	system("cls");
}
Timer Engine::time;
