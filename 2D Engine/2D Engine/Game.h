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

	static void AddTile(int sourceX, int sourceY, int xPosition, int yPosition);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector< ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Rect camera;
};

