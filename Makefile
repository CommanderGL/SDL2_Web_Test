SOURCE_DIR = src
OUT_DIR = bin

SHELL_FILE_PROD = shell_prod.html
SHELL_FILE_DEV = shell_dev.html

OBJS = main.cpp
OBJ_NAME = test

CC = em++

COMPILER_FLAGS = -g -lm --bind -s USE_SDL=2

NODE_PACKAGE_MANAGER = pnpm # For Watch Mode

build_prod:
	$(CC) $(SOURCE_DIR)/$(OBJS) -o $(OUT_DIR)/$(OBJ_NAME).html --shell-file $(SHELL_FILE_PROD) $(COMPILER_FLAGS)

build_dev:
	$(CC) $(SOURCE_DIR)/$(OBJS) -o $(OUT_DIR)/$(OBJ_NAME).html --shell-file $(SHELL_FILE_DEV) $(COMPILER_FLAGS)

watch_prod:
	$(NODE_PACKAGE_MANAGER) nodemon -w src/**/* -w $(SHELL_FILE_PROD) -e cpp,c,h,hpp,html -x "make build_prod || exit 0"

watch_dev:
	$(NODE_PACKAGE_MANAGER) nodemon -w src/**/* -w $(SHELL_FILE_DEV) -e cpp,c,h,hpp,html -x "make build_dev || exit 0"