#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
{

	window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (window) {
		renderer = SDL_CreateRenderer(window, NULL);
	}

}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(SDL_Texture* textr)
{
	//confirms that i can use the same texture multiple times
	SDL_FRect src;
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;


	SDL_FRect dest;
	dest.x = 100;
	dest.y = 100;
	dest.w = 32*4;
	dest.h = 32*4;

	SDL_FRect src2;
	src2.x = 0;
	src2.y = 0;
	src2.w = 32;
	src2.h = 32;


	SDL_FRect dest2;
	dest2.x = 200;
	dest2.y = 200;
	dest2.w = 32 * 4;
	dest2.h = 32 * 4;

	SDL_FRect src3;
	src3.x = 0;
	src3.y = 0;
	src3.w = 32;
	src3.h = 32;


	SDL_FRect dest3;
	dest3.x = 300;
	dest3.y = 300;
	dest3.w = 32 * 4;
	dest3.h = 32 * 4;


	SDL_RenderTexture(renderer, textr, &src, &dest);

	SDL_RenderTexture(renderer, textr, &src2, &dest2);

	SDL_RenderTexture(renderer, textr, &src3, &dest3);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}
