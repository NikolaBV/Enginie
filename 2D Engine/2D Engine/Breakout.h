#pragma once
#include "Scene.h"
#include "Game.h"
#include "Components.h"
#include "Groups.h"
#include "Collision.h"

#include <map>
#include <vector>
#include <sstream>

enum RectangleColor {
	Red,
	Orange,
	DarkGreen,
	LightGreen,
	DarkBlue,
};

struct RecntangleCollider {
	Entity* entity;
	RectangleColor color;
};

class Breakout : public Scene
{
public:
	void OnEnter(SceneContext& ctx) override;
	void OnExit(SceneContext& ctx) override;
	void HandleEvent(SceneContext& ctx, const SDL_Event& e) override;
	void Update(SceneContext& ctx) override;
	void Render(SceneContext& ctx) override;

	void DrawColliderRectanglesRow(RectangleColor color);
	void ResetRound();

private:
	Entity* playerPaddle = nullptr;
	Entity* ball = nullptr;
	Entity* scoreLabel = nullptr;

	int score = 0;
	int health = 3;
	int rectnagleColliderId = 0;

	const int COLLIDER_RECTANGLE_HEIGHT = 20;
	const int COLLIDER_RECTANGLE_WIDTH = 50;
	float collider_row_y_position = 250;

	int numberOfRectnaglesPerRow = Game::windowWidth / COLLIDER_RECTANGLE_WIDTH;

	std::map<RectangleColor, std::string> colorsTextureIdMap
	{
		{RectangleColor::DarkBlue, "darkBlueTile"},
		{RectangleColor::LightGreen, "lightGreenTile"},
		{RectangleColor::DarkGreen, "darkGreenTile"},
		{RectangleColor::Orange, "orangeTile"},
		{RectangleColor::Red, "redTile"},
	};
	std::map<int, RecntangleCollider> rectangleColliders;

};

