#include "Game.h"

Game* game = nullptr;
int main() {
    game = new Game();
    game->Init("First window", 640, 480, false);

    while (game->Running()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    game->Clean();
    return 0;
}