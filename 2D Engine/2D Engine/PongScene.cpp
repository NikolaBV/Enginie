#include "PongScene.h"
#include "Game.h"
#include "Groups.h"

void PongScene::OnEnter(SceneContext& ctx)
{
	leftPaddle = &manager.AddEntity();
	rightPaddle = &manager.AddEntity();
	ball = &manager.AddEntity();
	leftScoreLabel = &manager.AddEntity();
	rightScoreLabel = &manager.AddEntity();

	std::cout << "Pong scene loaded" << std::endl;

	int windowWidth = 0, windowHeight = 0;
	SDL_GetRendererOutputSize(Game::renderer, &windowWidth, &windowHeight);

	net.x = windowWidth / 2 - 2;
	net.y = 0;
	net.w = 4;
	net.h = windowHeight;

	assets.AddTexture("paddle", "resources/tiles/whiteTile.png");
	assets.AddFont("stardew", "resources/fonts/Stardew_Valley.otf", 16);

	//Setup entity texture ids in pars with the controls
	std::map<SDL_Scancode, const char*> leftPaddleKeyboardControlsMap = { {SDL_SCANCODE_W, "paddle"}, {SDL_SCANCODE_S, "paddle"} };

	leftPaddle->AddComponent<TransformComponent>(50, 320, 40, 5, 2);
	leftPaddle->AddComponent<SpriteComponent>(assets, "paddle", false);
	leftPaddle->AddComponent<ColliderComponent>("leftPaddle");
	leftPaddle->AddComponent<KeyboardController>(assets, Game::keyState, leftPaddleKeyboardControlsMap, false, true, InputScheme::WASD);
	leftPaddle->AddGroup(GroupLabels::groupPlayers);

	rightPaddle->AddComponent<TransformComponent>(750, 320, 40, 5, 2);
	rightPaddle->AddComponent<SpriteComponent>(assets, "paddle", false);
	rightPaddle->AddComponent<ColliderComponent>("rightPaddle");
	rightPaddle->AddComponent<KeyboardController>(assets, Game::keyState, leftPaddleKeyboardControlsMap, false, true, InputScheme::Arrows);
	rightPaddle->AddGroup(GroupLabels::groupPlayers);

	ball->AddComponent<TransformComponent>(450, 320, 5, 5, 2);
	ball->AddComponent<SpriteComponent>(assets, "paddle", false);
	ball->AddComponent<ColliderComponent>("ball");
	ball->AddGroup(GroupLabels::groupProjectiles);

	ball->GetComponent<TransformComponent>().velocity.x = -1;
	ball->GetComponent<TransformComponent>().velocity.y = 0.5f;

	SDL_Color whiteColor = { 255,255,255,255 };
	leftScoreLabel->AddComponent<UILabelComponent>(assets, 10, 10, "Score Player 1", "stardew", whiteColor);
	rightScoreLabel->AddComponent<UILabelComponent>(assets, 700,10, "Score Player 2", "stardew", whiteColor);

	Game::assets = &assets;

}

void PongScene::OnExit(SceneContext& ctx)
{
}

void PongScene::HandleEvent(SceneContext& ctx, const SDL_Event& e)
{
}

void PongScene::Update(SceneContext& ctx)
{
	//SDL_Rect leftPaddleCollider = leftPaddle->GetComponent<ColliderComponent>().collider;
	//Vector2D leftPaddlePosition = leftPaddle->GetComponent<TransformComponent>().position;

	//SDL_Rect rightPaddleCollider = rightPaddle->GetComponent<ColliderComponent>().collider;
	//Vector2D rightPaddlePosition = rightPaddle->GetComponent<TransformComponent>().position;

	SDL_Rect ballCollider = ball->GetComponent<ColliderComponent>().collider;
	Vector2D ballPosition = ball->GetComponent<TransformComponent>().position;
	Vector2D ballVelocity = ball->GetComponent<TransformComponent>().velocity;

	bool collidesTop = false;
	bool collidesBottom = false;
	bool collidesLeft = false;
	bool collidesRight = false;

	std::stringstream leftPaddleLabelStream;
	std::stringstream rightPaddleLabelStream;

	leftPaddleLabelStream << "Left score: " << leftScore;
	rightPaddleLabelStream << "Right score: " << rightScore;

	leftScoreLabel->GetComponent<UILabelComponent>().SetlabelText(leftPaddleLabelStream.str(), "stardew");
	rightScoreLabel->GetComponent<UILabelComponent>().SetlabelText(rightPaddleLabelStream.str(), "stardew");

	manager.refresh();
	manager.Update();

	//TODO Implement a proper defl;ection of the ball, dont just reverse its direrction
	if (Collision::AABB(rightPaddle->GetComponent<ColliderComponent>().collider, ball->GetComponent<ColliderComponent>().collider)) {
		std::cout << "Ball collided with right paddle" << std::endl;
		std::cout << "Ball collided with right paddle" << std::endl;
		ball->GetComponent<TransformComponent>().position = ballPosition;

		Vector2D normalVector;
		Vector2D objectVelocity = ballVelocity;

		std::cout << "objectVelocity vector" << objectVelocity << std::endl;

		normalVector.x = -1;
		normalVector.y = 0;

		std::cout << "Normal vector" << normalVector << std::endl;

		float dotProduct = normalVector.DotProduct(objectVelocity);
		std::cout << "Dot product" << dotProduct << std::endl;

		Vector2D normalVectorTimesDot;
		normalVectorTimesDot.x = normalVector.x * dotProduct;
		normalVectorTimesDot.y = normalVector.y * dotProduct;

		std::cout << "normal Vector TimesDot" << normalVectorTimesDot << std::endl;

		Vector2D twoProj;
		twoProj.x = normalVectorTimesDot.x * 2.0f;
		twoProj.y = normalVectorTimesDot.y * 2.0f;

		std::cout << "minus Two TimesResult" << twoProj << std::endl;

		Vector2D reflected;
		reflected.x = objectVelocity.x - twoProj.x;
		reflected.y = objectVelocity.y - twoProj.y;

		ball->GetComponent<TransformComponent>().velocity = reflected;
		std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;


	}
	if (Collision::AABB(leftPaddle->GetComponent<ColliderComponent>().collider, ball->GetComponent<ColliderComponent>().collider)) {
		std::cout << "Ball collided with right paddle" << std::endl;
		ball->GetComponent<TransformComponent>().position = ballPosition;

		Vector2D normalVector;
		Vector2D objectVelocity = ballVelocity;

		std::cout << "objectVelocity vector" << objectVelocity << std::endl;

		normalVector.x = -1;
		normalVector.y = 0;

		std::cout << "Normal vector" << normalVector << std::endl;

		float dotProduct = normalVector.DotProduct(objectVelocity);
		std::cout << "Dot product" << dotProduct << std::endl;

		Vector2D normalVectorTimesDot;
		normalVectorTimesDot.x = normalVector.x * dotProduct;
		normalVectorTimesDot.y = normalVector.y * dotProduct;

		std::cout << "normal Vector TimesDot" << normalVectorTimesDot << std::endl;

		Vector2D twoProj;
		twoProj.x = normalVectorTimesDot.x * 2.0f;
		twoProj.y = normalVectorTimesDot.y * 2.0f;

		std::cout << "minus Two TimesResult" << twoProj << std::endl;

		Vector2D reflected;
		reflected.x = objectVelocity.x - twoProj.x;
		reflected.y = objectVelocity.y - twoProj.y;

		ball->GetComponent<TransformComponent>().velocity = reflected;
		std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;
	}

	std::cout << "Collider: (x: " << ball->GetComponent<ColliderComponent>().collider.x<<", y: " << ball->GetComponent<ColliderComponent>().collider.y << std::endl;

	if (ball->GetComponent<ColliderComponent>().collider.y == 0) {
		collidesTop = true;
	}

	if (ball->GetComponent<ColliderComponent>().collider.y >= 640) {
		collidesBottom = true;
	}

	if (collidesTop){
		Vector2D normalVector;
		Vector2D objectVelocity = ballVelocity;

		std::cout << "objectVelocity vector: " << objectVelocity << std::endl;

		normalVector.x = 0;
		normalVector.y = 1;

		std::cout << "Normal vector: " << normalVector << std::endl;

		float dotProduct = normalVector.DotProduct(objectVelocity);
		std::cout << "Dot product: " << dotProduct << std::endl;

		Vector2D normalVectorTimesDot;
		normalVectorTimesDot.x = normalVector.x * dotProduct;
		normalVectorTimesDot.y = normalVector.y * dotProduct;

		std::cout << "normal Vector TimesDot: " << normalVectorTimesDot << std::endl;

		Vector2D twoProj;
		twoProj.x = normalVectorTimesDot.x * 2.0f;
		twoProj.y = normalVectorTimesDot.y * 2.0f;

		std::cout << "Two times result: " << twoProj << std::endl;

		Vector2D reflected;
		reflected.x = objectVelocity.x - twoProj.x;
		reflected.y = objectVelocity.y - twoProj.y;

		ball->GetComponent<TransformComponent>().velocity = reflected;
		std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;

		ball->GetComponent<TransformComponent>().position = ballPosition;
		collidesTop = false;
	}
	else if (collidesBottom) {
		Vector2D normalVector;
		Vector2D objectVelocity = ballVelocity;

		std::cout << "objectVelocity vector: " << objectVelocity << std::endl;

		normalVector.x = 0;
		normalVector.y = 1;

		std::cout << "Normal vector: " << normalVector << std::endl;

		float dotProduct = normalVector.DotProduct(objectVelocity);
		std::cout << "Dot product: " << dotProduct << std::endl;

		Vector2D normalVectorTimesDot;
		normalVectorTimesDot.x = normalVector.x * dotProduct;
		normalVectorTimesDot.y = normalVector.y * dotProduct;

		std::cout << "normal Vector TimesDot: " << normalVectorTimesDot << std::endl;

		Vector2D twoProj;
		twoProj.x = normalVectorTimesDot.x * 2.0f;
		twoProj.y = normalVectorTimesDot.y * 2.0f;

		std::cout << "Two times result: " << twoProj << std::endl;

		Vector2D reflected;
		reflected.x = objectVelocity.x - twoProj.x;
		reflected.y = objectVelocity.y - twoProj.y;

		ball->GetComponent<TransformComponent>().velocity = reflected;
		std::cout << "Ball velocity after collision: " << ball->GetComponent<TransformComponent>().velocity << std::endl;

		ball->GetComponent<TransformComponent>().position = ballPosition;
		collidesBottom = false;
	}


	//TODO Remove this, add proper score handling later
	leftScore++;
	rightScore++;


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