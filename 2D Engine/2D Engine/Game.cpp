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

const char* mapFile = "resources/tiles/tileset.png";

enum groupLables : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	Map::LoadMap("resources/maps/firstMap.map", 10, 10);

	player.AddComponent<TransformComponent>(1);
	player.AddComponent <SpriteComponent>("resources/standard/idle.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(groupPlayers);

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

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));
;

void Game::Render() {
	SDL_RenderClear(renderer);
	for (auto& tile : tiles) {
		tile->Draw();
	}
	for (auto& player : players) {
		player->Draw();
	}
	for (auto& enemy : enemies) {
		enemy->Draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	manager.refresh();
	manager.Update();

	for (auto collider : colliders) {
		Collision::AABB(player.GetComponent<ColliderComponent>(), *collider);
	}
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}

void Game::AddTile(int sourceX, int sourceY, int xPosition, int yPosition) {
	auto& tile(manager.AddEntity());
	// Use 32x32 tiles like in the tutorial so the map does not fill the entire window
	tile.AddComponent<TileComponent>(sourceX, sourceY, xPosition, yPosition, mapFile);
	tile.AddGroup(groupMap);
}