#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include "Scene.h"
#include "EventBus.h"
#include <RmlUi/Core.h>

class ColliderComponent;
class AssetManager;
class Scene;

class Game
{
private:
	SDL_Window* window;
	Scene* currentScene = nullptr;
	EventBus eventBus;
public:
	Game();
	~Game();

	void Init(const char* windowTitle, int height, int width, bool isFullscreen);

	void SetScene(Scene* scene);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const Uint8* keyState;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	static Rml::Context* context;
	static Rml::ElementDocument* document;
	static int windowWidth, windowHeight;
};

