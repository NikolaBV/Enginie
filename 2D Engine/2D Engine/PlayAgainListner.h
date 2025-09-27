#pragma once
#include <RmlUi/Core.h>
#include <iostream>
#include "PongScene.h"

class PlayAgainListner : public Rml::EventListener {
private:
	Scene* scene = nullptr;
public:
	PlayAgainListner(Scene* scene) : scene(scene){}
	void ProcessEvent(Rml::Event& event) override {
		std::cout << "Play again" << std::endl;
		scene->ResetGame();
	}

};
