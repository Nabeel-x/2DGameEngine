#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.hpp"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	SpriteComponent(const char* path,int nFrames,int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTex(path);
	}
	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		
		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, desRect);
	}
};