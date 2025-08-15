#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& firstRect, const SDL_Rect& secondRect); //ACCESS ALIGNED BOUNDING BOX
};

