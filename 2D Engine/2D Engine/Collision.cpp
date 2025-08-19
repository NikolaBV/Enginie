#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& firstRect, const SDL_Rect& secondRect) {
	if ((firstRect.x + firstRect.w >= secondRect.x) && (secondRect.x + secondRect.w >= firstRect.x)
		&& (firstRect.y + firstRect.h >= secondRect.y) && (secondRect.y + secondRect.h >= firstRect.y)) {
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& firstColliderObject, const ColliderComponent& secondColliderObject) {
	if (AABB(firstColliderObject.collider, secondColliderObject.collider)) {
		std::cout << firstColliderObject.tag << " collided with " << secondColliderObject.tag << std::endl;
		return true;
	}
	else {
		return false;
	}
}