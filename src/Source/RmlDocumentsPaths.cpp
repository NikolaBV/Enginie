#include "../Header/RmlDocumentsPaths.h"

std::map<DocumentPath, std::string> RmlDocumentsPaths::documentPaths = {
	{DocumentPath::LaptopMainMenu, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\main-menu\\hello_world.rml"},
	{DocumentPath::LaptopGlobalGameOver, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\global\\game-over.rml"},
	{DocumentPath::LaptopPongGameOver, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\pong\\game-over.rml"},
	{ DocumentPath::PCMainMenu, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\main-menu\\hello_world.rml" },
	{DocumentPath::PCGlobalGameOver, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\global\\game-over.rml"},
	{ DocumentPath::PCPongGameOver, "D:\\Programming\\C++\\Game Dev\\Enginie\\src\\resources\\ui\\rml\\pong\\game-over.rml" }
};
