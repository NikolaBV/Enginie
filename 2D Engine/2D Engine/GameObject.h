#pragma once
#include "Game.h"
class GameObject
{
private:
	int xPosition, yPosition;
	
	SDL_Texture *objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer *renderer;

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();
};

