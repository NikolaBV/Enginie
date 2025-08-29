#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "AssetManager.h"
#include "SandboxScene.h"
#include "Groups.h" 

#include <sstream>

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0, 800,640 };
AssetManager* Game::assets = nullptr;

bool Game::isRunning = false;

Game::Game() {}

Game::~Game() {}

void Game::Init(const char* windowTitle, int height, int width, bool isFullscreen) {

	int flags = 0;

	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL is initialized" << std::endl;

		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, flags);

		if (window) {
			std::cout << "Window is created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer) {
			std::cout << "Renderer is created" << std::endl;
		}

		isRunning = true;
	}

	char* base_path = SDL_GetBasePath();
	if (base_path) {
		SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
		SDL_free(base_path);
	}

	// Fonts
	if (TTF_Init() == -1) {
		std::cout << "Error loading SDL_TTF" << std::endl;
	}

	SetScene(new SandboxScene());
}

void Game::SetScene(Scene* scene) {
	if (currentScene) {
		SceneContext ctx{ *this };
		currentScene->OnExit(ctx);
	}
	currentScene = scene;
	if (currentScene) {
		SceneContext ctx{ *this};
		currentScene->OnEnter(ctx);
	}
}

void Game::HandleEvents() {
	SDL_PollEvent(&event);

	if (currentScene) {
		SceneContext ctx{ *this };
		currentScene->HandleEvent(ctx, event);
	}

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::Update() {

	if (currentScene) {
		SceneContext ctx{ *this };
		currentScene->Update(ctx);
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);

	if (currentScene) {
		SceneContext ctx{ *this };
		currentScene->Render(ctx);
	}

	SDL_RenderPresent(renderer);
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}