#pragma once
#include "Scene.h"

class TetrisScene : public Scene
{
	void OnEnter(SceneContext& ctx) override;
	void OnExit(SceneContext& ctx) override;
	void HandleEvent(SceneContext& ctx, const SDL_Event& e) override;
	void Update(SceneContext& ctx) override;
	void Render(SceneContext& ctx) override;
	void ResetGame() override;
};

