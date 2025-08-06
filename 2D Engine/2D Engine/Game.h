#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
#include <string>
#include <SDL_image.h>

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
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

	static SDL_Renderer* renderer;
};

