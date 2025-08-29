#include "SandboxScene.h"
#include "Groups.h"

void SandboxScene::OnEnter(SceneContext& sceneContext)
{
	playerEntity = &manager.AddEntity();
	assets.AddTexture("terrain", "resources/tiles/tileset.png");
	map = std::make_unique<Map>("terrain", 2, 64);

	map->LoadMap(assets, manager, "resources/maps/firstMap.map", 10, 10);

	assets.AddTexture("playerIdle", "resources/standard/idle.png");
	assets.AddTexture("playerWalk", "resources/standard/walk.png");

	assets.AddTexture("testProjectile", "resources/projectiles/testProjectile.png");

	assets.AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);


	//auto& label(sceneContext.manager.AddEntity());

	std::cout << "Adding player entity components" << std::endl;
	playerEntity->AddComponent<TransformComponent>(1.40f);
	playerEntity->AddComponent <SpriteComponent>(assets,"playerIdle", true);
	playerEntity->AddComponent<KeyboardController>(assets);
	playerEntity->AddComponent<ColliderComponent>("player");
	playerEntity->AddGroup(GroupLabels::groupPlayers);


	//SDL_Color whiteColor = { 255,255,255,255 };
	//label.AddComponent<UILabelComponent>(10, 10, "Testing new font", "stardew", whiteColor);

	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 0), 200, 2, "testProjectile");
	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 2), 200, 2, "testProjectile");
	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 1.5f), 100, 2, "testProjectile");

	Game::assets = &assets;
}

void SandboxScene::OnExit(SceneContext& sceneContext)
{
	Game::assets = nullptr;
}

void SandboxScene::HandleEvent(SceneContext& sceneContext, const SDL_Event& e)
{
}

void SandboxScene::Update(SceneContext& sceneContext)
{
	SDL_Rect playerCollider = playerEntity->GetComponent<ColliderComponent>().collider;
	Vector2D playerPosition = playerEntity->GetComponent<TransformComponent>().position;

	/*std::stringstream stringStream;
	stringStream << "Player position" << playerPosition;*/
	//labelEntity->GetComponent<UILabelComponent>().SetlabelText(stringStream.str(), "stardew");

	manager.refresh();
	manager.Update();

	auto& colliders = manager.GetGroup(GroupLabels::groupColliders);
	auto& projectiles = manager.GetGroup(GroupLabels::groupProjectiles);

	for (auto& collider : colliders) {
		SDL_Rect tempCollider = collider->GetComponent<ColliderComponent>().collider;
		if (Collision::AABB(tempCollider, playerCollider)) {
			playerEntity->GetComponent<TransformComponent>().position = playerPosition;
			std::cout << "Player hit collider" << std::endl;
		}
	}

	for (auto& projectile : projectiles) {
		if (Collision::AABB(playerEntity->GetComponent<ColliderComponent>().collider, projectile->GetComponent<ColliderComponent>().collider)) {
			std::cout << "Projectile hit player" << std::endl;
			projectile->Destroy();
		}
	}

	Game::camera.x = playerEntity->GetComponent<TransformComponent>().position.x - 400;
	Game::camera.y = playerEntity->GetComponent<TransformComponent>().position.y - 320;

	// Map size: 10x10 tiles * 128 pixels = 1280x1280 pixels
	const int mapWidth = 10 * 128;  // 1280 pixels
	const int mapHeight = 10 * 128; // 1280 pixels

	// Clamp camera to map boundaries
	if (Game::camera.x < 0) {
		Game::camera.x = 0;
	}
	if (Game::camera.y < 0) {
		Game::camera.y = 0;
	}
	if (Game::camera.x > mapWidth - Game::camera.w) {
		Game::camera.x = mapWidth - Game::camera.w;
	}
	if (Game::camera.y > mapHeight - Game::camera.h) {
		Game::camera.y = mapHeight - Game::camera.h;
	}
}

void SandboxScene::Render(SceneContext& sceneContext)
{
	auto& tiles(manager.GetGroup(GroupLabels::groupMap));
	auto& players(manager.GetGroup(GroupLabels::groupPlayers));
	auto& enemies(manager.GetGroup(GroupLabels::groupEnemies));
	auto& colliders(manager.GetGroup(GroupLabels::groupColliders));
	auto& projectiles(manager.GetGroup(GroupLabels::groupProjectiles));

	for (auto& tile : tiles) {
		tile->Draw();
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
}
