#pragma once
#include "Timer.h"


class Engine
{
public:
	Engine();
	~Engine();

	// What does static do?
	bool Init();
	bool gameLoop();

	static void Start();
	static void Stop();
	static void Update();

	static Timer time;
private:

};

