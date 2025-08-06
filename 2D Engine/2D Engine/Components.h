#pragma once
#include "EntityComponentSystem.h"

class PositionComponent : public Component {
private:
	int xPosition, yPosition;

public:
	int getX() { return xPosition; };
	int getY() { return yPosition; };

	void Init() override {
		xPosition = 0;
		yPosition = 0;
	}

	void SetPosition(int x, int y) {
		xPosition = x;
		yPosition = y;
	}

	void Update() override {
		xPosition++;
		yPosition++;
	}

};
class Components
{
};

