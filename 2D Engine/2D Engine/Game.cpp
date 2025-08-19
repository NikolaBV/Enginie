#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

auto& tileZero(manager.AddEntity());
auto& tileOne(manager.AddEntity());
auto& tileTwo(manager.AddEntity());

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

	tileZero.AddComponent<TileComponent>(200, 200, 64, 64, 0);
	tileOne.AddComponent<TileComponent>(250, 250, 64, 64, 1);
	tileTwo.AddComponent<TileComponent>(150, 150, 64, 64, 2);

	tileOne.AddComponent<ColliderComponent>("dirt");
	tileTwo.AddComponent<ColliderComponent>("grass");


	player.AddComponent<TransformComponent>(1);
	player.AddComponent <SpriteComponent>("resources/standard/walk.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");

	wall.AddComponent<TransformComponent>(100.0f, 100.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("resources/tiles/dirt.png");
	wall.AddComponent<ColliderComponent>("wall");

	std::cout << "Wall created at position: (100, 100) with size: 300x20" << std::endl;
};

void Game::HandleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::Render() {
	SDL_RenderClear(renderer);
	//map->DrawMap();
	manager.Draw();
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	manager.refresh();
	manager.Update();

	for (auto collider:colliders) {
		Collision::AABB(player.GetComponent<ColliderComponent>(), *collider);
	}
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}
