#include "PongScene.h"
#include "RmlDocumentsPaths.h"

Rml::ElementDocument* PongScene::gameOver = nullptr;

void PongScene::OnEnter(SceneContext& ctx)
{
	isRunningScene = true;
	leftPaddle = &manager.AddEntity();
	rightPaddle = &manager.AddEntity(); 
	ball = &manager.AddEntity();
	leftScoreLabel = &manager.AddEntity();
	rightScoreLabel = &manager.AddEntity();

	std::cout << "Pong scene loaded" << std::endl;

	SDL_GetRendererOutputSize(Game::renderer, &Game::windowWidth, &Game::windowHeight);

	net.x = Game::windowWidth / 2 - 2;
	net.y = 0;
	net.w = 4;
	net.h = Game::windowHeight;

	assets.AddTexture("paddle", "resources/tiles/whiteTile.png");
	assets.AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);

	//Setup entity texture ids in pars with the controls
	std::map<SDL_Scancode, const char*> leftPaddleKeyboardControlsMap = { {SDL_SCANCODE_W, "paddle"}, {SDL_SCANCODE_S, "paddle"} };

	leftPaddle->AddComponent<TransformComponent>(50.0f, 320.0f, 40, 5, 2.0f);
	leftPaddle->AddComponent<SpriteComponent>(assets, "paddle", false);
	leftPaddle->AddComponent<ColliderComponent>("Player 1");
	leftPaddle->AddComponent<KeyboardController>(assets, Game::keyState, leftPaddleKeyboardControlsMap, false, true, InputScheme::WASD);
	leftPaddle->AddGroup(GroupLabels::groupPlayers);

	rightPaddle->AddComponent<TransformComponent>(750.0f, 320.0f, 40, 5, 2.0f);
	rightPaddle->AddComponent<SpriteComponent>(assets, "paddle", false);
	rightPaddle->AddComponent<ColliderComponent>("Player 2");
	rightPaddle->AddComponent<KeyboardController>(assets, Game::keyState, leftPaddleKeyboardControlsMap, false, true, InputScheme::Arrows);
	rightPaddle->AddGroup(GroupLabels::groupPlayers);

	ball->AddComponent<TransformComponent>(450.0f, 320.0f, 5, 5, 2.0f);
	ball->AddComponent<SpriteComponent>(assets, "paddle", false);
	ball->AddComponent<ColliderComponent>("ball");
	ball->AddGroup(GroupLabels::groupProjectiles);

	ball->GetComponent<TransformComponent>().velocity = Vector2D(1.0f, 0.5f);


	SDL_Color whiteColor = { 255,255,255,255 };
	leftScoreLabel->AddComponent<UILabelComponent>(assets, 10, 10, "Score Player 1", "stardew", whiteColor);
	rightScoreLabel->AddComponent<UILabelComponent>(assets, 700, 10, "Score Player 2", "stardew", whiteColor);

	Game::assets = &assets;


	ctx.eventBus.Subscribe<EndGame>([this](const EndGame& e) {
		if (e.entity == leftPaddle || e.entity == rightPaddle) {
			pendingRestart = true;
			isRunningScene = false;

			playerWinner = e.entity->GetComponent<ColliderComponent>().tag;

			if (Rml::DataModelConstructor constructor = Game::context->CreateDataModel("winners"))
			{
				constructor.Bind("winner-player", &winner_data.winner_player);
				constructor.Bind("winner", &playerWinner);
			}
			//TODO Add a relative path to the document
			Rml::ElementDocument* localDocument = Game::context->LoadDocument(RmlDocumentsPaths::documentPaths[DocumentPath::LaptopPongGameOver]);
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
		}
		});
}

void PongScene::OnExit(SceneContext& ctx)
{
	if (leftPaddle) leftPaddle->Destroy();
	if (rightPaddle) rightPaddle->Destroy();
	if (ball) ball->Destroy();
	if (leftScoreLabel) leftScoreLabel->Destroy();
	if (rightScoreLabel) rightScoreLabel->Destroy();

	manager.refresh();

	if (gameOver) {
		gameOver->Close();
		gameOver = nullptr;
	}

	Game::assets = nullptr;

	leftPaddle = nullptr;
	rightPaddle = nullptr;
	ball = nullptr;
	leftScoreLabel = nullptr;
	rightScoreLabel = nullptr;
	pendingRestart = false;
	isRunningScene = false;
}

void PongScene::HandleEvent(SceneContext& ctx, const SDL_Event& e)
{
}

void PongScene::Update(SceneContext& ctx)
{
	if (isRunningScene) {
		SDL_Rect ballCollider = ball->GetComponent<ColliderComponent>().collider;
		Vector2D ballPosition = ball->GetComponent<TransformComponent>().position;
		Vector2D ballVelocity = ball->GetComponent<TransformComponent>().velocity;

		bool collidesTop = false, collidesBottom = false, collidesLeft = false, collidesRight = false;

		std::stringstream leftPaddleLabelStream, rightPaddleLabelStream;

		leftPaddleLabelStream << "Left score: " << leftScore;
		rightPaddleLabelStream << "Right score: " << rightScore;

		leftScoreLabel->GetComponent<UILabelComponent>().SetlabelText(leftPaddleLabelStream.str(), "stardew");
		rightScoreLabel->GetComponent<UILabelComponent>().SetlabelText(rightPaddleLabelStream.str(), "stardew");

		manager.refresh();
		manager.Update();

		if (pendingRestart) {
			std::cout << "Game over" << std::endl;
			ResetGame();
			pendingRestart = false;
			return;
		}
		if (Collision::AABB(rightPaddle->GetComponent<ColliderComponent>().collider, ball->GetComponent<ColliderComponent>().collider)) {
			Vector2D normalVector = Vector2D(-1, 0);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			float newSpeed = CalculateNewSpeed(1.80f);
			ball->GetComponent<TransformComponent>().velocity = reflection * static_cast<int>(newSpeed);
			std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;
		}
		if (Collision::AABB(leftPaddle->GetComponent<ColliderComponent>().collider, ball->GetComponent<ColliderComponent>().collider)) {
			Vector2D normalVector = Vector2D(-1, 0);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			float newSpeed = CalculateNewSpeed(1.80f);
			ball->GetComponent<TransformComponent>().velocity = reflection * static_cast<int>(newSpeed);
			std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;
		}

		if (ball->GetComponent<ColliderComponent>().collider.y == 0) {
			collidesTop = true;
		}

		if (ball->GetComponent<ColliderComponent>().collider.y >= Game::windowHeight) {
			collidesBottom = true;
		}

		if (ball->GetComponent<ColliderComponent>().collider.x <= 0) {
			collidesLeft = true;
		}
		if (ball->GetComponent<ColliderComponent>().collider.x >= Game::windowWidth) {
			collidesRight = true;
		}

		if (collidesTop || collidesBottom) {
			Vector2D normalVector = Vector2D(0, 1);
			Vector2D reflection = ballVelocity.Reflection(normalVector);
			ball->GetComponent<TransformComponent>().velocity = reflection;
		}

		if (collidesLeft) {
			rightScore++;
			leftPaddle->GetComponent<TransformComponent>().position = Vector2D(50.0f, 320.0f);
			rightPaddle->GetComponent<TransformComponent>().position = Vector2D(750.0f, 320.0f);
			ball->GetComponent<TransformComponent>().position = Vector2D(450.0f, 320.0f);
			currentSpeed = baseSpeed;
			ball->GetComponent<TransformComponent>().velocity = Vector2D(1.0f, -0.5f).Normalize() * static_cast<int>(currentSpeed);
		}
		else if (collidesRight) {
			leftScore++;
			leftPaddle->GetComponent<TransformComponent>().position = Vector2D(50.0f, 320.0f);
			rightPaddle->GetComponent<TransformComponent>().position = Vector2D(750.0f, 320.0f);
			ball->GetComponent<TransformComponent>().position = Vector2D(450.0f, 320.0f);
			currentSpeed = baseSpeed;
			ball->GetComponent<TransformComponent>().velocity = Vector2D(1.0f, -0.5f).Normalize() * static_cast<int>(currentSpeed);
		}

		if (leftScore >= maxScore) {
			std::cout << "Left player won" << std::endl;
			ctx.eventBus.Publish(EndGame{ leftPaddle });
		}
		else if (rightScore >= maxScore) {
			std::cout << "Right player won" << std::endl;
			ctx.eventBus.Publish(EndGame{ rightPaddle });
		}
	}
	else {
		return;
	}
}

void PongScene::Render(SceneContext& ctx)
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &net);

	auto& players(manager.GetGroup(GroupLabels::groupPlayers));
	auto& projectiles(manager.GetGroup(GroupLabels::groupProjectiles));


	for (auto& player : players) {
		player->Draw();
	}
	for (auto& projectile : projectiles) {
		projectile->Draw();
	}

	leftScoreLabel->Draw();
	rightScoreLabel->Draw();
}

void PongScene::ResetGame()
{
	rightScore = 0;
	leftScore = 0;

	leftPaddle->GetComponent<TransformComponent>().position = Vector2D(50.0f, 320.0f);
	rightPaddle->GetComponent<TransformComponent>().position = Vector2D(750.0f, 320.0f);
	ball->GetComponent<TransformComponent>().position = Vector2D(450.0f, 320.0f);

	ball->GetComponent<TransformComponent>().velocity = Vector2D(1.0f, -0.5f);

	if (gameOver) {
		gameOver->Close();
	}
	isRunningScene = true;
	pendingRestart = false;
}

float PongScene::CalculateNewSpeed(float increasePercentage)
{
	return  currentSpeed * increasePercentage;
}
