#pragma once
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	TileComponent() = default;
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		desRect.x = xpos;
		desRect.y = ypos;
		desRect.w = desRect.h = 64;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, desRect, SDL_FLIP_NONE);
	}
};