#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <vector>

class ColliderComponent;

class Game
{
private:
	SDL_Window* window;
public:
	Game();
	~Game();

	void Init(const char* windowTitle, int height, int width, bool isFullscreen);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	enum groupLables : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders
	};
};

