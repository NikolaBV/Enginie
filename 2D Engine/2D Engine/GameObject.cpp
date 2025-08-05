#include "GameObject.h"
#include "TextureManager.h"

const float OBJECT_SIZE_SCALER = 1.50f;

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y) {
	xPosition = x;
	yPosition = y;
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(textureSheet, renderer);
}

void GameObject::Update() {
	sourceRect.w = 64;
	sourceRect.h = 64;

	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = xPosition;
	destinationRect.x = yPosition;

	destinationRect.w = sourceRect.w * OBJECT_SIZE_SCALER;
	destinationRect.h = sourceRect.h * OBJECT_SIZE_SCALER;


}
void GameObject::Render() {
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}