#pragma once
#include "EntityComponentSystem.h"
#include "AssetManager.h"
#include "Game.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class UILabelComponent : public Component
{
public:
	AssetManager localAssetManager = nullptr;

	UILabelComponent();

	UILabelComponent(AssetManager& assetManager,int xPosition, int yPosition, std::string text, std::string font, SDL_Color& textColor)
		: localAssetManager(assetManager), labelText(text), labelFont(font), textColor(textColor) {
		position.x = xPosition;
		position.y = yPosition;

		SetlabelText(labelText, labelFont);

	};
	~UILabelComponent() {};

	void SetlabelText(std::string text, std::string font) {
		SDL_Surface* surface = TTF_RenderText_Blended(localAssetManager.GetFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}
	void Draw() {
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}
private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
};

