#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_a:
				sprite->play("Walk");
				transform->velocity.x = -1;
				break;
			case SDLK_d:
				sprite->play("Walk");
				transform->velocity.x = 1;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				sprite->play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				sprite->play("Idle");
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				sprite->play("Idle");
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				sprite->play("Idle");
				transform->velocity.x = 0;
			default:
				break;
			}
		}
	}
};