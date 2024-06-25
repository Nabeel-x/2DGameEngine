#pragma once
#include "Components.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 72;
	int width = 48;

	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(int sc) {
		position.Zero();
		scale = sc;
	}
	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override {
		velocity.Zero();
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};