OBJS = *.cpp

CC = g++
EM = em++
WIN = cl

TYPE=DEBUG

INCLUDE_PATHS = -IE:/Go/mingw_dev_lib/include/SDL2

LIBRARY_PATHS = -LE:/Go/mingw_dev_lib/lib

COMPILER_FLAGS = -w -W

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

WEB_FLAGS = -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS='["png"]'

RELEASE_FLAGS = -O3 -Wall -DNDEBUG

OBJ_NAME = ../build/pong

WEB_OBJ_NAME = ../build/pong.html

DEBUG_LOG_PATH = ../debug/log.txt

RELEASE_PATH = ../build/release/pong

WEB_PRELOAD = --preload-file W:/Game/pong/assets/fonts/Play-Regular.ttf@../assets/fonts/Play-Regular.ttf

all:
	make build-debug
	make run

build-debug:
	$(CC) -g $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
build-release:
	$(CC) $(RELEASE_FLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_PATH)
build-web:
	$(EM) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(WEB_FLAGS) -o $(WEB_OBJ_NAME) $(WEB_PRELOAD)

run:
	./$(OBJ_NAME) > $(DEBUG_LOG_PATH)

