#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Collision.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;
Manager manager;
std::vector<ColliderComponent*> Game::colliders;

auto& Player(manager.addEntity());
auto& Wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game() {

}

Game::~Game() {

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
		if (window) {
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	} else {
		isRunning = false;
	}
	map = new Map();
	if (map) {
		std::cout << "Map added" << std::endl;
	}
	tile0.addComponent<TileComponent>(200,200,32,32,0);
	tile1.addComponent<TileComponent>(250,250,32,32,1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150,150,32,32,2);
	tile2.addComponent<ColliderComponent>("grass");


	Player.addComponent<TransformComponent>(0.0f,0.0f,100,100,1);
	Player.addComponent<SpriteComponent>("assets/adwait100no.png");
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("player");

	Wall.addComponent<TransformComponent>(300.0f,300.0f,100,115,1);
	Wall.addComponent<SpriteComponent>("assets/dirt.png");
	Wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	Vector2D playerPos = Player.getComponent<TransformComponent>().position;
	manager.refresh();
	manager.update();
	for (auto cc : colliders) {
		Collision::AABB(Player.getComponent<ColliderComponent>(), *cc);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}