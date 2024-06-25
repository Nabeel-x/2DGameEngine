#pragma once
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	Vector2D position;
	TileComponent() = default;
	~TileComponent() {
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);
		position.x = xpos;
		position.y = ypos;
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		desRect.x = xpos;
		desRect.y = ypos;
		desRect.w = desRect.h = 64;
	}
	void update() override {
		desRect.x = position.x - Game::camera.x;
		desRect.y = position.y - Game::camera.y;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, desRect, SDL_FLIP_NONE);
	}
};