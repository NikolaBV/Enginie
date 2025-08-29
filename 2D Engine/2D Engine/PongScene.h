#pragma once
#include "Scene.h"

class PongScene : public Scene {
public:
	void OnEnter(SceneContext& ctx) override;
	void OnExit(SceneContext& ctx) override;
	void HandleEvent(SceneContext& ctx, const SDL_Event& e) override;
	void Update(SceneContext& ctx) override;
	void Render(SceneContext& ctx) override;
private:
	Entity* leftPaddle = nullptr;
	Entity* rightPaddle = nullptr;
	Entity* ball = nullptr;
	Entity* scoreLabel = nullptr;
	int leftScore = 0, rightScore = 0;
	void ResetRound(SceneContext& ctx);
};