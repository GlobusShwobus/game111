
#include <SDL3/SDL.h>

int main() {

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("title", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* render= SDL_CreateRenderer(window, NULL);

	bool gameRunning = true;
	SDL_Event event;

	while (gameRunning) {

		SDL_PollEvent(&event);

		if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
			gameRunning = false;
		}
		//asd
	}

	SDL_Quit();

	return 0;
}