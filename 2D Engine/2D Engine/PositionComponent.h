#pragma once
#include "EntityComponentSystem.h"

class PositionComponent : public Component {
private:
	int xPosition, yPosition;

public:
	PositionComponent() {
		xPosition = 0;
		yPosition = 0;
	}
	PositionComponent(int x, int y) {
		xPosition = x;
		yPosition = y;
	}

	int getX() { return xPosition; };
	int getY() { return yPosition; };

	void SetPosition(int x, int y) {
		xPosition = x;
		yPosition = y;
	}
	void setX(int x) {
		xPosition = x;
	}
	void setY(int y) {
		yPosition = y;
	}
	void Update() override {
		xPosition++;
		yPosition++;
	}

};