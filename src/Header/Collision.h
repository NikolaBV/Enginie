#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& firstRect, const SDL_Rect& secondRect); //ACCESS ALIGNED BOUNDING BOX
	static bool AABB(const ColliderComponent& firstColliderObject, const ColliderComponent& secondColliderObject);
	static bool IntersectsWithDistanceBased(const SDL_Rect& firstRect, const SDL_Rect& secondRect);

};

