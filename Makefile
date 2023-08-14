SOURCE_DIR = src
OUT_DIR = bin

SHELL_FILE = shell.html

OBJS = main.cpp
OBJ_NAME = test

CC = em++

COMPILER_FLAGS = -g -lm --bind -s ALLOW_MEMORY_GROWTH -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets/ --use-preload-plugins
WATCH_FLAGS = -w src/**/* -w assets/**/* -w $(SHELL_FILE) -e cpp,c,h,hpp,html -x "make build || exit 0"

NODE_PACKAGE_MANAGER = pnpm # For Watch Mode

build:
	$(CC) $(SOURCE_DIR)/$(OBJS) -o $(OUT_DIR)/$(OBJ_NAME).html --shell-file $(SHELL_FILE) $(COMPILER_FLAGS)

build_default_shell:
	$(CC) $(SOURCE_DIR)/$(OBJS) -o $(OUT_DIR)/$(OBJ_NAME).html $(COMPILER_FLAGS)

watch:
	$(NODE_PACKAGE_MANAGER) nodemon $(WATCH_FLAGS)