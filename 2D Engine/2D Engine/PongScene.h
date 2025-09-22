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
#include <RmlUi/Core.h>

class PongScene : public Scene {
public:
	void OnEnter(SceneContext& ctx) override;
	void OnExit(SceneContext& ctx) override;
	void HandleEvent(SceneContext& ctx, const SDL_Event& e) override;
	void Update(SceneContext& ctx) override;
	void Render(SceneContext& ctx) override;
	void ResetGame();
	Rml::String playerWinner = "";
	float CalculateNewSpeed(float increasePercentage);

private:
	Entity* leftPaddle = nullptr;
	Entity* rightPaddle = nullptr;

	Entity* ball = nullptr;
	Entity* leftScoreLabel = nullptr;
	Entity* rightScoreLabel = nullptr;
	SDL_Rect net;

	int leftScore = 0, rightScore = 0;
	int maxScore = 2;
	float baseSpeed = 1.0f;
	float currentSpeed = baseSpeed;

	bool pendingRestart = false;
	bool isRunningScene = false;

	static Rml::ElementDocument* gameOver;
};