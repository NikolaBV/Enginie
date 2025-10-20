#include "../Header/Breakout.h"
#include "../Header/RmlDocumentsPaths.h"
Rml::ElementDocument* Breakout::gameOver = nullptr;

void Breakout::OnEnter(SceneContext& ctx)
{
	isRunningScene = true;

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

	assets.AddSoundEffect("fart", "resources/sound/sound.wav");

	std::map<SDL_Scancode, const char*> playerControlsMap = { {SDL_SCANCODE_A, "whiteTile"}, {SDL_SCANCODE_D, "whiteTile"} };

	playerPaddle->AddComponent<TransformComponent>(360.0f, 550.0f, 5, 80, 2.0f);
	playerPaddle->AddComponent<SpriteComponent>(assets, "whiteTile", false);
	playerPaddle->AddComponent<KeyboardController>(assets, Game::keyState, playerControlsMap, true, false, InputScheme::WASD);
	playerPaddle->AddComponent<ColliderComponent>("player");
	playerPaddle->AddGroup(GroupLabels::groupPlayers);

	ball->AddComponent<TransformComponent>(400.0f, 400.0f, 5, 5, 2.0f);
	ball->AddComponent<SpriteComponent>(assets, "whiteTile", false);
	ball->AddComponent<ColliderComponent>("ball");
	ball->AddGroup(GroupLabels::groupProjectiles);

	ball->GetComponent<TransformComponent>().velocity = Vector2D(0.8f, 1);

	SDL_Color whiteColor = { 255,255,255,255 };
	scoreLabel->AddComponent<UILabelComponent>(assets, 10, 10, "Score", "stardew", whiteColor);

	for (int colorInt = Red; colorInt <= 4; colorInt++) {
		DrawColliderRectanglesRow(static_cast<RectangleColor>(colorInt));
	}
	rectnagleColliderId = 0;


	ctx.eventBus.Subscribe<EndGame>([this](const EndGame& e) {
	
			pendingRestart = true;
			isRunningScene = false;

			Rml::ElementDocument* localDocument = Game::context->LoadDocument(RmlDocumentsPaths::documentPaths[DocumentPath::PCGlobalGameOver]);
			gameOver = localDocument;

			if (localDocument != NULL) {
				localDocument->Show();
			}
			else {
				std::cout << "Problem loading document" << std::endl;
			}

			Rml::Element* gameOverButton = gameOver->GetElementById("quit-game");
			Rml::Element* playAgainButton = gameOver->GetElementById("play-again");

			if (gameOverButton) {
				static QuitGameListener quitListener;
				gameOverButton->AddEventListener("click", &quitListener);
			}
			if (playAgainButton) {
				static PlayAgainListner playAgainListner(this);
				playAgainButton->AddEventListener("click", &playAgainListner);
			}
		});

	Game::assets = &assets;

	assets.PlaySound("fart");

}

void Breakout::OnExit(SceneContext& ctx)
{
}

void Breakout::HandleEvent(SceneContext& ctx, const SDL_Event& e)
{
}

void Breakout::Update(SceneContext& ctx)
{
	if (isRunningScene) {
		SDL_Rect playerCollider = playerPaddle->GetComponent<ColliderComponent>().collider;
		Vector2D initlialPlayerPosition = playerPaddle->GetComponent<TransformComponent>().position;

		Vector2D initlialBallPosition = ball->GetComponent<TransformComponent>().position;
		SDL_Rect ballCollider = ball->GetComponent<ColliderComponent>().collider;
		Vector2D ballVelocity = ball->GetComponent<TransformComponent>().velocity;

		std::stringstream scoreStream;
		scoreStream << "Score " << score;
		scoreLabel->GetComponent<UILabelComponent>().SetlabelText(scoreStream.str(), "stardew");

		manager.refresh();
		manager.Update();

		if (pendingRestart) {
			std::cout << "Game over" << std::endl;
			ResetGame();
			pendingRestart = false;
			isRunningScene = true;
			return;
		}

		auto& colliders = manager.GetGroup(GroupLabels::groupColliders);
		auto& projectiles = manager.GetGroup(GroupLabels::groupProjectiles);

		for (auto& collider : colliders) {
			if (Collision::AABB(ball->GetComponent<ColliderComponent>().collider, collider->GetComponent<ColliderComponent>().collider)) {
				Vector2D normalVector = Vector2D(0, 1);
				Vector2D reflection = ballVelocity.Reflection(normalVector);

				std::string tag = collider->GetComponent<ColliderComponent>().tag;
				RecntangleCollider  rectangleCollider = rectangleColliders[stoi(tag)];
				ball->GetComponent<TransformComponent>().velocity = reflection;
				rectangleCollider.entity->Destroy();
				rectangleColliders.erase(stoi(tag));
				std::cout << tag << " destroyed" << std::endl;

				score++;
				return;
			}
		}

		//TODO Make a fucntion in Collison class to detect collision with all sides of the window and return true if so
		if (ball->GetComponent<ColliderComponent>().collider.x >= Game::windowWidth) {
			Vector2D normalVector = Vector2D(1, 0);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			ball->GetComponent<TransformComponent>().velocity = reflection;
		}
		if (ball->GetComponent<ColliderComponent>().collider.x <= 0) {
			Vector2D normalVector = Vector2D(1, 0);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			ball->GetComponent<TransformComponent>().velocity = reflection;
		}
		if (Collision::AABB(playerPaddle->GetComponent<ColliderComponent>().collider, ball->GetComponent<ColliderComponent>().collider)) {
			Vector2D normalVector = Vector2D(0, 1);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			ball->GetComponent<TransformComponent>().velocity = reflection;
		}
		if (ball->GetComponent<ColliderComponent>().collider.y == 0) {
			Vector2D normalVector = Vector2D(0, 1);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			ball->GetComponent<TransformComponent>().velocity = reflection;
			return;
		}

		if (ball->GetComponent<ColliderComponent>().collider.y >= Game::windowHeight) {
			ResetRound();
			return;
		}

		if (health <= 0) {
			//TODO Implement a game over event
			ctx.eventBus.Publish(EndGame{ playerPaddle });
		}
	}
	else {
		return;
	}

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

	scoreLabel->Draw();
}

void Breakout::DrawColliderRectanglesRow(RectangleColor color)
{
	float xPosition = 0;
	for (int i = 0; i <= numberOfRectnaglesPerRow; i++) {
		Entity* tempRectangleEntity = nullptr;

		tempRectangleEntity = &manager.AddEntity();

		tempRectangleEntity->AddComponent<TransformComponent>(static_cast<float>(xPosition), static_cast<float>(collider_row_y_position), COLLIDER_RECTANGLE_HEIGHT, COLLIDER_RECTANGLE_WIDTH, 1);
		tempRectangleEntity->AddComponent<SpriteComponent>(assets, colorsTextureIdMap[color], false);
		tempRectangleEntity->AddGroup(GroupLabels::groupColliders);
		tempRectangleEntity->AddComponent<ColliderComponent>(std::to_string(rectnagleColliderId));

		RecntangleCollider newRectangleCollider;
		newRectangleCollider.entity = tempRectangleEntity;
		newRectangleCollider.color = color;

		rectangleColliders.insert({ rectnagleColliderId, newRectangleCollider });

		xPosition += COLLIDER_RECTANGLE_WIDTH;
		rectnagleColliderId++;
	}
	collider_row_y_position += COLLIDER_RECTANGLE_HEIGHT;
}

void Breakout::ResetRound()
{
	health--;
	std::cout << "Heath: " << health << std::endl;
	ball->GetComponent<TransformComponent>().position = Vector2D(400.0f, 400.0f);
	ball->GetComponent<TransformComponent>().velocity = Vector2D(0.8f, 1);
}
float Breakout::CalculateNewSpeed(float increasePercentage)
{
	return currentSpeed * increasePercentage;
}
void Breakout::ResetGame()
{
	//TODO implement a reset game
	std::cout << "Reset game" << std::endl;
	score = 0;
	ball->GetComponent<TransformComponent>().position = Vector2D(400.0f, 400.0f);
	playerPaddle->GetComponent<TransformComponent>().position = Vector2D(360.0f, 550.0f);

	if (gameOver) {
		gameOver->Close();
	}

	health = 3;
	isRunningScene = true;
	pendingRestart = false;
}
