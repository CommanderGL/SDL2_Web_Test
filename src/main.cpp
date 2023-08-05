#include <SDL2/SDL.h>
#include <emscripten.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
SDL_Window* window = NULL;

SDL_Event e;
bool quit = false;

void update() {
	while (SDL_PollEvent(&e)) {
		if( e.type == SDL_QUIT ) quit = true;
	}

	if (quit) {
		emscripten_cancel_main_loop();

		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

int main(int argc, char* args[]) {
	SDL_Surface* screenSurface = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
	SDL_UpdateWindowSurface(window);

	emscripten_set_main_loop(update, 0, 1);

	/* SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if( e.type == SDL_QUIT ) quit = true;
		}
	} */

	/* SDL_DestroyWindow(window);
	SDL_Quit(); */
	return 0;
}