#pragma once
#include "Scene.h"
#include "Map.h"
#include "Components.h"
#include "TransformComponent.h"
#include "Collision.h"
#include "UILabelComponent.h"
#include "ColliderComponent.h"
#include "InputScheme.h"

#include <sstream>
#include <vector>

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
	Entity* leftScoreLabel = nullptr;
	Entity* rightScoreLabel = nullptr;
	SDL_Rect net;

	int leftScore = 0, rightScore = 0;
	void ResetRound(SceneContext& ctx);
};