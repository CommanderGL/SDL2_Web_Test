SOURCE_DIR = src
OUT_DIR = bin

OBJS = main.cpp
OBJ_NAME = test

CC = em++

COMPILER_FLAGS = -g -lm --bind -s USE_SDL=2

all: build

build:
	$(CC) $(SOURCE_DIR)/$(OBJS) -o $(OUT_DIR)/$(OBJ_NAME).html $(COMPILER_FLAGS)