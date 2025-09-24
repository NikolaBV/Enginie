#include "Breakout.h"

void Breakout::OnEnter(SceneContext& ctx)
{
	std::cout << "Breakout scene loaded" << std::endl;

	playerPaddle = &manager.AddEntity();
	ball = &manager.AddEntity();
	scoreLabel = &manager.AddEntity();

	assets.AddTexture("whiteTile", "resources/tiles/whiteTile.png");
	assets.AddTexture("darkBlueTile", "resources/tiles/darkBlueTile.png");
	assets.AddTexture("lightGreenTile", "resources/tiles/lightGreenTile.png");
	assets.AddTexture("darkGreenTile", "resources/tiles/darkGreenTile.png");
	assets.AddTexture("orangeTile", "resources/tiles/orangeTile.png");
	assets.AddTexture("redTile", "resources/tiles/redTile.png");

	assets.AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);

	std::map<SDL_Scancode, const char*> playerControlsMap = { {SDL_SCANCODE_A, "whiteTile"}, {SDL_SCANCODE_D, "whiteTile"} };

	playerPaddle->AddComponent<TransformComponent>(360.0f, 550.0f, 5, 80, 2.0f);
	playerPaddle->AddComponent<SpriteComponent>(assets, "whiteTile", false);
	playerPaddle->AddComponent<KeyboardController>(assets, Game::keyState, playerControlsMap, true, false, InputScheme::WASD);
	playerPaddle->AddGroup(GroupLabels::groupPlayers);

	ball->AddComponent<TransformComponent>(400.0f, 400.0f, 5, 5, 2.0f);
	ball->AddComponent<SpriteComponent>(assets, "whiteTile", false);
	ball->AddGroup(GroupLabels::groupProjectiles);


	std::cout << "Darkblue: " << static_cast<RectangleColor>(DarkBlue) << std::endl;

	for (int colorInt = Red; colorInt <= 4; colorInt++) {
		DrawColliderRectanglesRow(static_cast<RectangleColor>(colorInt));
	}

	Game::assets = &assets;
}

void Breakout::OnExit(SceneContext& ctx)
{
}

void Breakout::HandleEvent(SceneContext& ctx, const SDL_Event& e)
{
}

void Breakout::Update(SceneContext& ctx)
{
	manager.refresh();
	manager.Update();
}

void Breakout::Render(SceneContext& ctx)
{
	auto& players(manager.GetGroup(GroupLabels::groupPlayers));
	auto& projectiles(manager.GetGroup(GroupLabels::groupProjectiles));
	auto& colliders(manager.GetGroup(GroupLabels::groupColliders));

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

void Breakout::DrawColliderRectanglesRow(RectangleColor color)
{
	float xPosition = 0;
	for (int i = 0; i <= numberOfRectnaglesPerRow; i++) {
		Entity* tempRectangleEntity = nullptr;

		tempRectangleEntity = &manager.AddEntity();

		RecntangleCollider newRectangleCollider;
		newRectangleCollider.entity = tempRectangleEntity;

		tempRectangleEntity->AddComponent<TransformComponent>(static_cast<float>(xPosition), static_cast<float>(collider_row_y_position), COLLIDER_RECTANGLE_HEIGHT, COLLIDER_RECTANGLE_WIDTH, 2.0f);
		tempRectangleEntity->AddComponent<SpriteComponent>(assets, colorsTextureIdMap[color], false);
		tempRectangleEntity->AddGroup(GroupLabels::groupColliders);

		rectangleColliders.push_back(newRectangleCollider);
		xPosition += COLLIDER_RECTANGLE_WIDTH;
	}
	collider_row_y_position += COLLIDER_RECTANGLE_HEIGHT * 2;
}
