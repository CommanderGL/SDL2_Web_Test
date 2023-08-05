#include <SDL2/SDL.h>
#include <emscripten.h>
#include <string>
#include "log.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Joystick* joy = NULL;

SDL_Event e;
bool quit = false;

bool down = false;

void update() {
	Uint32 color = SDL_MapRGB(screenSurface->format, 0x00, 0xff, 0x00);
	if (joy == NULL && SDL_NumJoysticks() > 0) {
		joy = SDL_JoystickOpen(0);
	}
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) quit = true;
		if (e.type == SDL_JOYBUTTONDOWN) {
			log::info(std::to_string(e.jbutton.button).c_str());
			down = true;
		} else if (e.type == SDL_JOYBUTTONUP) {
			down = false;
		}
	}

	if (down) {
		color = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xff);
	}

	SDL_FillRect(screenSurface, NULL, color);
	SDL_UpdateWindowSurface(window);

	if (quit) {
		emscripten_cancel_main_loop();

		SDL_JoystickClose(joy);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);

	SDL_JoystickEventState(SDL_ENABLE);

	emscripten_set_main_loop(update, 0, 1);

	return 0;
}