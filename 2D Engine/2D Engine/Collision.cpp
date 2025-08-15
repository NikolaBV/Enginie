#include "Collision.h"

bool Collision::AABB(const SDL_Rect& firstRect, const SDL_Rect& secondRect) {
	if ((firstRect.x + firstRect.w >= secondRect.x) && (secondRect.x + secondRect.w >= firstRect.x)
		&& (firstRect.y + firstRect.h >= secondRect.y) && (secondRect.y + secondRect.h >= firstRect.y)) {
		return true;
	}
	return false;
}