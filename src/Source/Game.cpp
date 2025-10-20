#include "../Header/Game.h"
#include "../Header/TextureManager.h"
#include "../Header/Map.h"
#include "../Header/Components.h"
#include "../Header/Collision.h"
#include "../Header/AssetManager.h"
#include "../Header/Groups.h" 
#include "../Header/RmlDocumentsPaths.h"


#include "../rmlui_backends/RmlUi_Platform_SDL.h"
#include "../rmlui_backends/RmlUi_Renderer_SDL.h"

#include "../Header/SandboxScene.h"
#include "../Header/PongScene.h"
#include "../Header/Breakout.h"
#include "../Header/TetrisScene.h"


#include "../Header/QuitGameListner.h"
#include "../Header/StartGameListner.h"

#include <windows.h>
#include <Lmcons.h>
#include <sstream>
#include <memory>
#include "SDL_mixer.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;
Rml::Context* Game::context = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0, 800,640 };
AssetManager* Game::assets = nullptr;
const Uint8* Game::keyState = NULL;
bool Game::isRunning = false;
Rml::ElementDocument* Game::document = nullptr;
Rml::EventListener* eventListner;
int Game::windowHeight = 0;
int Game::windowWidth = 0;

Game::Game() {}

Game::~Game() {}

void Game::Init(const char* windowTitle, int width, int height, bool isFullscreen) {
	//TODO Use this for the rml file paths somehow
	//TCHAR name[UNLEN + 1];
	//DWORD size = UNLEN + 1;

	//if (GetUserName((TCHAR*)name, &size))
	//	std::wcout << L"Hello, " << name << L"!\n";
	//else
	//	std::cout << "Hello, unnamed person!\n";
#pragma region SDL Initlization
	int flags = 0;

	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	 
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL is initialized" << std::endl;

		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

		if (window) {
			std::cout << "Window is created" << std::endl;
			windowHeight = height;
			windowWidth = width;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer) {
			std::cout << "Renderer is created" << std::endl;
		}

		// Initialize SDL_mixer
		int mix_flags = MIX_INIT_OGG | MIX_INIT_MP3;
		if ((Mix_Init(mix_flags) & mix_flags) != mix_flags) {
			std::cout << "SDL_mixer init error: " << Mix_GetError() << std::endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << "SDL_mixer open audio error: " << Mix_GetError() << std::endl;
		}

		isRunning = true;
	}

	char* base_path = SDL_GetBasePath();
	if (base_path) {
		SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
		SDL_free(base_path);
	}

	// Fonts
	if (TTF_Init() == -1) {
		std::cout << "Error loading SDL_TTF" << std::endl;
	}

	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ((IMG_Init(img_flags) & img_flags) != img_flags) {
		std::cout << "Error initializing SDL_image" << std::endl;
	}
#pragma endregion

#pragma region Rml initialization logic
	static std::unique_ptr<SystemInterface_SDL> rml_system_interface;
	static std::unique_ptr<RenderInterface_SDL> rml_render_interface;

	rml_system_interface = std::make_unique<SystemInterface_SDL>();
	rml_system_interface->SetWindow(window);
	Rml::SetSystemInterface(rml_system_interface.get());

	rml_render_interface = std::make_unique<RenderInterface_SDL>(renderer);
	Rml::SetRenderInterface(rml_render_interface.get());

	bool rmlInit = Rml::Initialise();

	if (rmlInit) {
		std::cout << "rmlInit initlised" << std::endl;
	}

	Rml::Context* localContext = Rml::CreateContext("default", Rml::Vector2i(width, height));
	if (localContext) {
		std::cout << "RmlUi context initlised" << std::endl;
		context = localContext;
	}
	else {
		std::cout << "ERROR: RmlUi context failed" << std::endl;
		return;
	}

	bool success = Rml::LoadFontFace("resources/fonts/Stardew_Valley.otf");

	if (success) {
		std::cout << "Font loaded in RML" << std::endl;
	}
	//TODO FIX THE DOCUMENT PATH TO A RELATIVE ONE
	Rml::ElementDocument* localDocument = context->LoadDocument(RmlDocumentsPaths::documentPaths[DocumentPath::PCMainMenu]);
	document = localDocument;

	if (localDocument != NULL) {
		localDocument->Show();
	}
	else {
		std::cout << "Problem loading document" << std::endl;
	}

	Rml::Element* element = document->GetElementById("quit-game");

	if (element) {
		static QuitGameListener quitListener;
		element->AddEventListener("click", &quitListener);
	}
	else {
		std::cout << "Could not find quit-game element" << std::endl;
	}

	if (Rml::Element* startSandboxElement = document->GetElementById("start-sandbox")) {
		static StartGameListener startSandboxListner(this, new SandboxScene());
		startSandboxElement->AddEventListener("click", &startSandboxListner);
	}

	if (Rml::Element* startPongElement = document->GetElementById("start-pong")) {
		static StartGameListener startListener(this, new PongScene());
		startPongElement->AddEventListener("click", &startListener);
	}
	if (Rml::Element* startBreakoutElement = document->GetElementById("start-breakout")) {
		static StartGameListener startListener(this, new Breakout());
		startBreakoutElement->AddEventListener("click", &startListener);
	}
	if (Rml::Element* startBreakoutElement = document->GetElementById("start-tetris")) {
		static StartGameListener startListener(this, new TetrisScene());
		startBreakoutElement->AddEventListener("click", &startListener);
	}
	else {
		std::cout << "Could not find start-game element" << std::endl;
	}

#pragma endregion
}

void Game::SetScene(Scene* scene) {
	if (currentScene) {
		SceneContext ctx{ *this, eventBus };
		currentScene->OnExit(ctx);
	}
	currentScene = scene;
	if (currentScene) {
		SceneContext ctx{ *this, eventBus };
		currentScene->OnEnter(ctx);
	}
}

void Game::HandleEvents() {
	SDL_PollEvent(&event);
	if (RmlSDL::InputEventHandler(context, event))

		if (currentScene) {
			SceneContext ctx{ *this, eventBus };
			currentScene->HandleEvent(ctx, event);
		}

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void Game::Update() {
	Game::keyState = SDL_GetKeyboardState(NULL);
	context->Update();

	if (currentScene) {
		SceneContext ctx{ *this, eventBus };
		currentScene->Update(ctx);
	}
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (currentScene) {
		SceneContext ctx{ *this, eventBus };
		currentScene->Render(ctx);
	}

	context->Render();

	SDL_RenderPresent(renderer);
}


void Game::Clean() {
	if (context) {
		Rml::RemoveContext(context->GetName());
		context = nullptr;
	}
	Rml::Shutdown();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	context = nullptr;
	renderer = nullptr;
	keyState = nullptr;
	assets = nullptr;

	std::cout << "Game has been cleaned" << std::endl;
}