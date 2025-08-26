#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

SDL_Rect Game::camera = { 0,0, 800,640 };

bool Game::isRunning = false;

auto& player(manager.AddEntity());

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

	map = new Map("resources/tiles/tileset.png", 2, 64);
	map->LoadMap("resources/maps/firstMap.map", 10, 10);

	player.AddComponent<TransformComponent>(1.40f);
	player.AddComponent <SpriteComponent>("resources/standard/idle.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(groupPlayers);

	std::cout << "Wall created at position: (100, 100) with size: 300x20" << std::endl;
};

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& enemies(manager.GetGroup(Game::groupEnemies));
auto& colliders(manager.GetGroup(Game::groupColliders));


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
	for (auto& tile : tiles) {
		tile->Draw();
	}

	for (auto& collider : colliders) {
		collider->Draw();
	}

	for (auto& player : players) {
		player->Draw();
	}
    for (auto& collider : colliders) {
        collider->Draw();
    }

	SDL_RenderPresent(renderer);
}

void Game::Update() {

	SDL_Rect playerCollider = player.GetComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.GetComponent<TransformComponent>().position;

	manager.refresh();
	manager.Update();


	for (auto& collider : colliders) {
		SDL_Rect tempCollider = collider->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(tempCollider, playerCollider)) {
			player.GetComponent<TransformComponent>().position = playerPosition;
		}
	}

	camera.x = player.GetComponent<TransformComponent>().position.x - 400; 
	camera.y = player.GetComponent<TransformComponent>().position.y - 320;

	// Map size: 10x10 tiles * 128 pixels = 1280x1280 pixels
	const int mapWidth = 10 * 128;  // 1280 pixels
	const int mapHeight = 10 * 128; // 1280 pixels

	// Clamp camera to map boundaries
	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > mapWidth - camera.w) {
		camera.x = mapWidth - camera.w;
	}
	if (camera.y > mapHeight - camera.h) {
		camera.y = mapHeight - camera.h;
	}

}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}