#pragma once
#include <RmlUi/Core.h>
#include "Game.h"

class StartGameListener : public Rml::EventListener {
private:
	Game* game = nullptr;
	Scene* scene = nullptr;
public:
	StartGameListener(Game* game, Scene* scene) : game(game), scene(scene) {}
	void ProcessEvent(Rml::Event& event) override {
		std::cout << "Start game button from UI clicked" << std::endl;
		if (game != nullptr && scene != nullptr) {
			game->SetScene(scene);
			game->document->Clone();
		}
		if (Game::document != nullptr) {
			Game::document->Hide();
		}
	}
};
