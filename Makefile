OBJS = *.cpp

CC = g++

TYPE=DEBUG

INCLUDE_PATHS = -IE:/Go/mingw_dev_lib/include/SDL2

LIBRARY_PATHS = -LE:/Go/mingw_dev_lib/lib

COMPILER_FLAGS = -w -W

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

RELEASE_FLAGS = -O3 -Wall -DNDEBUG

OBJ_NAME = ../build/pong

DEBUG_LOG_PATH = ../debug/log.txt

RELEASE_PATH = ../build/release/pong

all:
	make build-debug
	make run

build-debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
build-release:
	$(CC) $(RELEASE_FLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_PATH)

run:
	./$(OBJ_NAME) > $(DEBUG_LOG_PATH)

