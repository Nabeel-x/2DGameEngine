#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
	}
	SpriteComponent(const char* path,bool isAnimated) {
		animated = isAnimated;
		Animation idle = Animation(0, 7, 100);
		Animation walk = Animation(1, 7, 100);
		Animation run = Animation(2, 8, 100);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Run", run);
		play("Idle");
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
		srcRect.y = animIndex * transform->height;
		desRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		desRect.y = static_cast<int>(transform->position.y) - Game:: camera.y;
		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;
	}
	void draw() override {
		TextureManager::Draw(texture, srcRect, desRect,spriteFlip);
	}
	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};