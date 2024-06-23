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

enum groupLabel :std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
};
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

	Map::LoadMap("assets/map.map",16,16);
	Player.addComponent<TransformComponent>(0.0f,0.0f,128,128,1);
	Player.addComponent<SpriteComponent>("assets/anims.png",true);
	Player.addComponent<KeyboardController>();
	Player.addComponent<ColliderComponent>("player");
	Player.addGroup(groupPlayers);
	Wall.addComponent<TransformComponent>(500.0f,300.0f,115,100,1);
	Wall.addComponent<SpriteComponent>("assets/dirt.png");
	Wall.addComponent<ColliderComponent>("wall");
	Wall.addGroup(groupMap);
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
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x,y,32,32,id);
	tile.addGroup(groupMap);
}