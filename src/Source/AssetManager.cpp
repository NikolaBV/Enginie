#include "../Header/AssetManager.h"
#include "../Header/Components.h"
#include "../Header/Groups.h"

AssetManager::AssetManager(Manager* manager) :manager(manager) {

}
AssetManager::~AssetManager() {

}

void AssetManager::CreateProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string textureId, int damage)
{
	auto& projectile(manager->AddEntity());
	projectile.AddComponent<TransformComponent>(position.x, position.y, 64, 64, 1.0f);
	projectile.AddComponent<SpriteComponent>(*this, textureId, false);
	projectile.AddComponent<ProjectileComponent>(range, speed, velocity, damage);
	projectile.AddComponent<ColliderComponent>("projectile");
	projectile.AddGroup(GroupLabels::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::AddFont(std::string fontId, std::string path, int fontSize)
{
	fonts.emplace(fontId, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId)
{
	return fonts[fontId];
}

void AssetManager::AddSoundEffect(std::string tag, std::string url)
{
	Mix_Chunk* soundEffect = Mix_LoadWAV(url.c_str());
	soundEffects.emplace(tag, soundEffect);
	soundEffect = nullptr;
}

void AssetManager::GetSoundEffect(std::string tag)
{
}

void AssetManager::RemoveSoundEffect(std::string tag)
{
}

void AssetManager::PlaySound(std::string tag)
{
	Mix_PlayChannel(-1, soundEffects[tag], 0);
}

void AssetManager::StopSound(std::string tag)
{
}
