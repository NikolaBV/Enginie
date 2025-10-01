#pragma once
#include <RmlUi/Core.h>
#include <iostream>
#include "Game.h"

class QuitGameListener : public Rml::EventListener {
public:
	void ProcessEvent(Rml::Event& event) override {
		std::cout << "Quit game button from UI clicked" << std::endl;
		Game::isRunning = false;
	}
};
