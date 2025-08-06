#include "GameObject.h"
#include "TextureManager.h"

const float OBJECT_SIZE_SCALER = 1.50f;

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objectTexture = TextureManager::LoadTexture(textureSheet);
	xPosition = x;
	yPosition = y;
}

void GameObject::Update() {

	xPosition++;
	yPosition++;

	sourceRect.w = 64; //Size of a single spirte in the sheet
	sourceRect.h = 64;

	sourceRect.x = 0; //0 Means beginning to crop from the top left of the sprite sheet
	sourceRect.y = 0;

	destinationRect.x = xPosition;
	destinationRect.y = yPosition;

	destinationRect.w = sourceRect.w * OBJECT_SIZE_SCALER;
	destinationRect.h = sourceRect.h * OBJECT_SIZE_SCALER;


}
void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRect, &destinationRect);
}