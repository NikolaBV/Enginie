#include "Game.h"

Game* game = nullptr;
int main() {

    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->Init("First window", 800, 640, false);

    while (game->Running()) {
        frameStart = SDL_GetTicks(); //How many milisecs since SDL was initilized

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart; //How long did the game loop iteration (a frame) take 

        //check if we need to delay running the next frame
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    game->Clean();
    return 0;
}