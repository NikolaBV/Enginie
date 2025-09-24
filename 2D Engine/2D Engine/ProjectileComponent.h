#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component
{
private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;

public:
	int damage = 0;

	ProjectileComponent() = default;

	ProjectileComponent(int range, int speed, Vector2D velocity, unsigned int damage) :range(range), speed(speed), velocity(velocity), damage(damage) {

	}
	~ProjectileComponent(){}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		transform->velocity = velocity;
		std::cout << "Projectile transform position: " << transform->position << std::endl;
	}
	void Update() override {
		distance += speed;
		if (distance > range) {
			std::cout << "Out of range" << std::endl;
			entity->Destroy();
		}
		//TODO DOuble check if this works
		else if (transform->position.x > Game::camera.x + Game::camera.w
			|| transform->position.x < Game::camera.x
			|| transform->position.y > Game::camera.y + Game::camera.h
			|| transform->position.y < Game::camera.y) {

			std::cout << "Out of bounds" << std::endl;
			entity->Destroy();
		}
	}

};

