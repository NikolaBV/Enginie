#include "SandboxScene.h"
#include "Groups.h"

void SandboxScene::OnEnter(SceneContext& sceneContext)
{
	isRunningScene = true;
	playerEntity = &manager.AddEntity();
	labelEntity = &manager.AddEntity();

	assets.AddTexture("terrain", "resources/tiles/tileset.png");
	map = std::make_unique<Map>("terrain", 2, 64);

	map->LoadMap(assets, manager, "resources/maps/firstMap.map", 10, 10);

	assets.AddTexture("playerIdle", "resources/standard/idle.png");
	assets.AddTexture("playerWalk", "resources/standard/walk.png");

	assets.AddTexture("testProjectile", "resources/projectiles/testProjectile.png");

	assets.AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);

	std::cout << "Adding player entity components" << std::endl;

    std::map<SDL_Scancode, const char*> playerKeyboardControlsMap = { {SDL_SCANCODE_W, "playerWalk"} };

	playerEntity->AddComponent<TransformComponent>(1.40f);
	playerEntity->AddComponent <SpriteComponent>(assets, "playerIdle", true);
	playerEntity->AddComponent<KeyboardController>(assets, Game::keyState, playerKeyboardControlsMap, true, true);
	playerEntity->AddComponent<ColliderComponent>("player");
	playerEntity->AddComponent<HealthComponent>(100, 0, sceneContext.eventBus);
	playerEntity->AddGroup(GroupLabels::groupPlayers);

	sceneContext.eventBus.Subscribe<DiedEvent>([this](const DiedEvent& e) {
		if (e.entity == playerEntity) {
			pendingRestart = true;
			isRunningScene = false;
			Game::document->Show();
		}
		});

	SDL_Color whiteColor = { 255,255,255,255 };
	labelEntity->AddComponent<UILabelComponent>(assets, 10, 10, "Testing new font", "stardew", whiteColor);

	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 0), 200, 2, "testProjectile", 80);
	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 0), 200, 2, "testProjectile", 20);
	assets.CreateProjectile(Vector2D(100, 300), Vector2D(2, 1.5f), 100, 2, "testProjectile", -10);

	Game::assets = &assets;
}

void SandboxScene::OnExit(SceneContext& sceneContext)
{
	Game::assets = nullptr;
	playerEntity = nullptr;
}

void SandboxScene::HandleEvent(SceneContext& sceneContext, const SDL_Event& e)
{
}

void SandboxScene::Update(SceneContext& sceneContext)
{
	if (isRunningScene) {
		playerEntity->GetComponent<KeyboardController>().localKeyState = Game::keyState;
		SDL_Rect playerCollider = playerEntity->GetComponent<ColliderComponent>().collider;
		Vector2D playerPosition = playerEntity->GetComponent<TransformComponent>().position;
		Vector2D playerVelocity = playerEntity->GetComponent<TransformComponent>().velocity;

		std::stringstream stringStream;
		stringStream << "Player position: " << "(" << playerPosition.x << ", " << playerPosition.y << ") ";
		stringStream << "Player velocity: " << "(x : " << playerVelocity.x << ", y : " << playerVelocity.y << ")";

		labelEntity->GetComponent<UILabelComponent>().SetlabelText(stringStream.str(), "stardew");

		manager.refresh();
		manager.Update();

		if (pendingRestart) {
			std::cout << "Game restarting..." << std::endl;
			OnExit(sceneContext);
			pendingRestart = false;
			return;
		}

		auto& colliders = manager.GetGroup(GroupLabels::groupColliders);
		auto& projectiles = manager.GetGroup(GroupLabels::groupProjectiles);

		for (auto& collider : colliders) {
			SDL_Rect tempCollider = collider->GetComponent<ColliderComponent>().collider;
			if (Collision::IntersectsWithDistanceBased(tempCollider, playerCollider)) {
				playerEntity->GetComponent<TransformComponent>().position = playerPosition;
			}
		}

		for (auto& projectile : projectiles) {
			if (Collision::IntersectsWithDistanceBased(playerEntity->GetComponent<ColliderComponent>().collider, projectile->GetComponent<ColliderComponent>().collider)) {
				std::cout << "Projectile hit player" << std::endl;
				std::cout << "Projectile damage: " << projectile->GetComponent<ProjectileComponent>().damage << std::endl;
				playerEntity->GetComponent<HealthComponent>().ApplyDamage(projectile->GetComponent<ProjectileComponent>().damage, projectile->GetComponent<ColliderComponent>().tag);
				std::cout << "Player Health: " << playerEntity->GetComponent<HealthComponent>().GetHealth() << std::endl;
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
	else {
		return;
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

	for (auto& collider : colliders) {
		collider->Draw();
	}
	for (auto& player : players) {
		player->Draw();
	}
	for (auto& projectile : projectiles) {
		projectile->Draw();
	}

	labelEntity->Draw();
}
