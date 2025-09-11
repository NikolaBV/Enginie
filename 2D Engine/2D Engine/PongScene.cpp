#include "PongScene.h"
#include "Game.h"
#include "Groups.h"

void PongScene::OnEnter(SceneContext& ctx)
{
	leftPaddle = &manager.AddEntity();

	std::cout << "Pong scene loaded" << std::endl;

	int windowWidth = 0, windowHeight = 0;
	SDL_GetRendererOutputSize(Game::renderer, &windowWidth, &windowHeight);

	net.x = windowWidth / 2 - 2;
	net.y = 0;
	net.w = 4;
	net.h = windowHeight;

	assets.AddTexture("paddle", "resources/tiles/whiteTile.png");

	auto tex = assets.GetTexture("paddle");
	if (!tex) { std::cerr << "Failed to load paddle texture\n"; }


	std::cout << "Adding left paddle entity components" << std::endl;

	//Setup entity texture ids in pars with the controls
	std::map<SDL_Scancode, const char*> leftPaddleKeyboardControlsMap = { {SDL_SCANCODE_W, "paddle"}, {SDL_SCANCODE_S, "paddle"} };


	leftPaddle->AddComponent<TransformComponent>(50, 320, 40, 5, 2);
	leftPaddle->AddComponent<SpriteComponent>(assets, "paddle", false);
	leftPaddle->AddComponent<ColliderComponent>("leftPaddle");
	leftPaddle->AddComponent<KeyboardController>(assets, Game::keyState, leftPaddleKeyboardControlsMap, false, true);


	leftPaddle->AddGroup(GroupLabels::groupPlayers);

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
	manager.refresh();
	manager.Update();
}

void PongScene::Render(SceneContext& ctx)
{
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &net);

	auto& players(manager.GetGroup(GroupLabels::groupPlayers));

	for (auto& player : players) {
		player->Draw();
	}
}