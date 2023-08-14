#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <emscripten.h>
#include "log.hpp"
#include "buttons.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define JOY_DEAD_Y 10000
#define JOY_DEAD_X 25000

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

typedef struct Vector2 {
	int x;
	int y;
} Vector2;

int down = -1;

SDL_Texture* load_texture(const char* path) {
	SDL_Surface* loaded_surface = IMG_Load(path);
	SDL_Texture* loaded_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	SDL_FreeSurface(loaded_surface);
	return loaded_texture;
}

class Player {
	public:
		SDL_Rect rect;
		Vector2 vel;
		SDL_Texture* texture;

		Player() {
			rect = (SDL_Rect){
				10, // x
				10, // y
				50, // width
				50 // height
			};
		};

		void load() {
			texture = load_texture("../assets/test.png");
		}

		void onEvent(SDL_Event e) {
			if (e.type == SDL_JOYAXISMOTION) {
				if (e.jaxis.axis == 0) {
					if (e.jaxis.value < -JOY_DEAD_X) {
						vel.x = -2;
					} else if (e.jaxis.value > JOY_DEAD_X) {
						vel.x = 2;
					} else {
						vel.x = 0;
					}
				} else if (e.jaxis.axis == 1) {
					if (e.jaxis.value < -JOY_DEAD_Y) {
						vel.y = -2;
					} else if (e.jaxis.value > JOY_DEAD_Y) {
						vel.y = 2;
					} else {
						vel.y = 0;
					}
				}
			}
		};

		void update() {
			rect.x += vel.x;
			if (vel.x == 0) rect.y += vel.y;
		};

		void draw() {
			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}
};

Player player;

SDL_Joystick* joy = NULL;

SDL_Event e;
bool quit = false;

void update() {
	if (joy == NULL && SDL_NumJoysticks() > 0) {
		joy = SDL_JoystickOpen(0);
	}
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) quit = true;
		if (e.type == SDL_JOYBUTTONDOWN) {
			down = e.jbutton.button;
		} else if (e.type == SDL_JOYBUTTONUP) {
			down = -1;
		}

		player.onEvent(e);
	}
	
	player.update();

	SDL_RenderClear(renderer);

	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, "Test Game", (SDL_Color){ 0x0, 0x0, 0x0 });
	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_Rect fontRect = {
		100, // x
		100, // y
		fontSurface->w, // width
		fontSurface->h // height
	};
	SDL_RenderCopy(renderer, fontTexture, NULL, &fontRect);
	
	SDL_FreeSurface(fontSurface);
	SDL_DestroyTexture(fontTexture);

	player.draw();
	SDL_RenderPresent(renderer);

	if (quit) {
		emscripten_cancel_main_loop();

		SDL_JoystickClose(joy);
		SDL_DestroyWindow(window);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}
}

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	font = TTF_OpenFont("../assets/NotoSans-SemiBold.ttf", 24);

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	SDL_JoystickEventState(SDL_ENABLE);

	player.load();

	emscripten_set_main_loop(update, 0, 1);

	return 0;
}