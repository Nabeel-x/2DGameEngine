#pragma once
#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static void addTile(int srcX, int srcY, int xpos, int ypos);
	static std::vector<ColliderComponent*>colliders;
	static bool isRunning;
	static SDL_Rect camera;
private:
	int counter = 0;
	SDL_Window* window;
};

#endif