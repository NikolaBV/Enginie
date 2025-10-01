#include "../Header/Collision.h"
#include "../Header/ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& firstRect, const SDL_Rect& secondRect) {
	if ((firstRect.x + firstRect.w >= secondRect.x) && (secondRect.x + secondRect.w >= firstRect.x)
		&& (firstRect.y + firstRect.h >= secondRect.y) && (secondRect.y + secondRect.h >= firstRect.y)) {
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& firstColliderObject, const ColliderComponent& secondColliderObject) {
	if (AABB(firstColliderObject.collider, secondColliderObject.collider)) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::IntersectsWithDistanceBased(const SDL_Rect& firstRect, const SDL_Rect& secondRect)
{
	// Tune this: higher = smaller hitbox
	const float shrink = 8.0f;

	float firstCenterX = firstRect.x + firstRect.w * 0.5f;
	float firstCenterY = firstRect.y + firstRect.h * 0.5f;
	float secondCenterX = secondRect.x + secondRect.w * 0.5f;
	float secondCenterY = secondRect.y + secondRect.h * 0.5f;

	float deltaX = firstCenterX - secondCenterX;
	float deltaY = firstCenterY - secondCenterY;

	float firstRadius = 0.5f * (firstRect.w < firstRect.h ? firstRect.w : firstRect.h) - shrink;
	float secondRadius = 0.5f * (secondRect.w < secondRect.h ? secondRect.w : secondRect.h) - shrink;

	if (firstRadius < 0.0f) firstRadius = 0.0f;
	if (secondRadius < 0.0f) secondRadius = 0.0f;

	float combinedRadius = firstRadius + secondRadius;
	return (deltaX * deltaX + deltaY * deltaY) <= (combinedRadius * combinedRadius);
}