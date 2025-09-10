#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Groups.h" 

#include <memory>

#include "rmlui_backends/RmlUi_Platform_SDL.h"
#include "rmlui_backends/RmlUi_Renderer_SDL.h"

#include "SandboxScene.h"
#include "PongScene.h"

#include <sstream>

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

Game::Game() {}

Game::~Game() {}


struct ApplicationData {
	bool show_text = true;
	Rml::String animal = "dog";
} my_data;

class QuitGameListener : public Rml::EventListener {
public:
	void ProcessEvent(Rml::Event& event) override {
		std::cout << "Quit game button from UI clicked" << std::endl;
		Game::isRunning = false;
	}
};

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
		}
		if (Game::document != nullptr) {
			Game::document->Hide();
		}
	}
};


void Game::Init(const char* windowTitle, int height, int width, bool isFullscreen) {

#pragma region SDLInitlization
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

	bool rmlInit =  Rml::Initialise();

	if (rmlInit) {
		std::cout << "rmlInit initlised" << std::endl;
	}

	Rml::Context* localContext = Rml::CreateContext("default", Rml::Vector2i(height, width));
	if (localContext) {
		std::cout << "RmlUi context initlised" << std::endl;
	}
	context = localContext;

	bool success = Rml::LoadFontFace("resources/fonts/Stardew_Valley.otf");

	if (success) {
		std::cout << "Font loaded in RML" << std::endl;
	}


	if (Rml::DataModelConstructor constructor = context->CreateDataModel("animals"))
	{
		constructor.Bind("show_text", &my_data.show_text);
		constructor.Bind("animal", &my_data.animal);
	}


	Rml::ElementDocument* localDocument = context->LoadDocument("D:\\Programming\\C++\\Game Dev\\Enginie\\2D Engine\\2D Engine\\resources\\ui\\hello_world.rml");
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

	if (Rml::Element* startElement = document->GetElementById("start-game")) {
		static StartGameListener startListener(this, new SandboxScene());
		startElement->AddEventListener("click", &startListener);
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

	context = nullptr;
	renderer = nullptr;
	keyState = nullptr;
	assets = nullptr;

	std::cout << "Game has been cleaned" << std::endl;
}