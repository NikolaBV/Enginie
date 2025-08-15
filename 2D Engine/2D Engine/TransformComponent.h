#pragma once
#include "EntityComponentSystem.h"
#include "Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 64;
	int width = 64;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int scale) {
		position.Zero();

		this->scale = scale;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int height, int width, int scale) {
		position.x = x;
		position.y = y;

		this->height = height;
		this->width = width;
		this->scale= scale;
	}


	void Init() override {
		velocity.Zero();
	}

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};