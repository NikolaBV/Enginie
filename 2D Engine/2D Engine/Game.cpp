#include "Game.h"

SDL_Texture *playerTexture;
SDL_Rect sourceRect, destinationRect;

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}
 
Game::Game() {
	
}

Game::~Game() {

}

void Game::Init(const char *windowTitle, int height, int width, bool isFullscreen) {

	int flags = 0;

	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL is initialized" << std::endl;

		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, flags);

		if (window) {
			std::cout << "Window is created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer) {
			std::cout << "Renderer is created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
};

void Game::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
} 

void Game::Render() {
	SDL_RenderClear(renderer);
	//Add stuff to render here
	playerTexture = LoadTexture("resources/standard/walk.png", renderer);
	SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRect);
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	ctr++;
	destinationRect.h = 64;
	destinationRect.w = 64;

	destinationRect.x = ctr;

	std::cout << "counter: " << ctr << std::endl;
}

void Game::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game has been cleaned" << std::endl;
}
