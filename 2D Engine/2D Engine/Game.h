#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
#include <string>

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer* renderer;
	int ctr;
public:
	Game();
	~Game();

	void Init(const char *windowTitle, int height, int width, bool isFullscreen);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };
};

