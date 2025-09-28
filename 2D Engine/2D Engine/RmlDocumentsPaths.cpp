#include "RmlDocumentsPaths.h"

std::map<DocumentPath, std::string> RmlDocumentsPaths::documentPaths = {
	{DocumentPath::LaptopMainMenu, "C:\\Programming\\C++\\Enginie\\2D Engine\\2D Engine\\resources\\ui\\rml\\main-menu\\hello_world.rml"},
	{DocumentPath::LaptopGlobalGameOver, "C:\\Programming\\C++\\Enginie\\2D Engine\\2D Engine\\resources\\ui\\rml\\global\\game-over.rml"},
	{DocumentPath::LaptopPongGameOver, "C:\\Programming\\C++\\Enginie\\2D Engine\\2D Engine\\resources\\ui\\rml\\pong\\game-over.rml"}
};
void RmlDocumentsPaths::Init() {
}