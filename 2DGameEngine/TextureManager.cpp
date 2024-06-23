#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer,tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect des) {
	SDL_RenderCopy(Game::renderer, tex, &src, &des);
}
