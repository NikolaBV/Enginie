#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
Manager manager;
auto& player(manager.AddEntity());

Game::Game() {

}

Game::~Game() {

}

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

	// Set working directory to executable directory for proper resource loading
	char* base_path = SDL_GetBasePath();
	if (base_path) {
		SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
		// Note: SDL doesn't have a direct chdir function, but we can use the base path
		// The resources should be copied to the executable directory
		SDL_free(base_path);
	}

	map = new Map();

	player.AddComponent<TransformComponent>(0,0);
	player.AddComponent <SpriteComponent>("resources/standard/walk.png");
};

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.Draw(); 
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	manager.refresh();
	manager.Update();

	player.GetComponent<TransformComponent>().position.Add(Vector2D(5, 5));

	if (player.GetComponent<TransformComponent>().position.x > 100) {
		player.GetComponent<SpriteComponent>().SetTexture("resources/standard/sit.png");
	}
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}
