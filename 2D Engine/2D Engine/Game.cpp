#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

SDL_Rect Game::camera = { 0,0, 800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.AddEntity());
auto& label(manager.AddEntity());

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

	//TODO Make a function for loading assets

	if (TTF_Init() == -1) {
		std::cout << "Error loading SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "resources/tiles/tileset.png");
	assets->AddTexture("playerIdle", "resources/standard/idle.png");
	assets->AddTexture("playerWalk", "resources/standard/walk.png");

	assets->AddTexture("testProjectile", "resources/projectiles/testProjectile.png");

	assets->AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);

	map = new Map("terrain", 2, 64);
	map->LoadMap("resources/maps/firstMap.map", 10, 10);

	player.AddComponent<TransformComponent>(1.40f);
	player.AddComponent <SpriteComponent>("playerIdle", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(groupPlayers);


	SDL_Color whiteColor = { 255,255,255,255 };
	label.AddComponent<UILabelComponent>(10, 10, "Testing new font", "stardew", whiteColor);

	assets->CreateProjectile(Vector2D(100, 300), Vector2D(2, 0), 200, 2, "testProjectile");
	assets->CreateProjectile(Vector2D(100, 300), Vector2D(2, 2), 200, 2, "testProjectile");
	assets->CreateProjectile(Vector2D(100, 300), Vector2D(2, 1.5f), 100, 2, "testProjectile");

};

auto& tiles(manager.GetGroup(Game::groupMap));
auto& players(manager.GetGroup(Game::groupPlayers));
auto& enemies(manager.GetGroup(Game::groupEnemies));
auto& colliders(manager.GetGroup(Game::groupColliders));
auto& projectiles(manager.GetGroup(Game::groupProjectiles));

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

	for (auto& projectile : projectiles) {
		projectile->Draw();
	}
	
	label.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Update() {

	SDL_Rect playerCollider = player.GetComponent<ColliderComponent>().collider;
	Vector2D playerPosition = player.GetComponent<TransformComponent>().position;

	std::stringstream stringStream;
	stringStream << "Player position" << playerPosition;
	label.GetComponent<UILabelComponent>().SetlabelText(stringStream.str(), "stardew");

	manager.refresh();
	manager.Update();


	for (auto& collider : colliders) {
		SDL_Rect tempCollider = collider->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(tempCollider, playerCollider)) {
			player.GetComponent<TransformComponent>().position = playerPosition;
		}
	}

	for (auto& projectile : projectiles) {
		if (Collision::AABB(player.GetComponent<ColliderComponent>().collider, projectile->GetComponent<ColliderComponent>().collider)) {
			std::cout << "Projectile hit player" << std::endl;
			projectile->Destroy();
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