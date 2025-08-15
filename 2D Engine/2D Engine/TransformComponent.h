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
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(int scale) {
		position.x = 0.0f;
		position.y = 0.0f;

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
		velocity.x = 0;
		velocity.y = 0;
	}

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};