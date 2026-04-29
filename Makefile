PLATFORM ?= linux

ifeq ($(PLATFORM), windows)
CC = x86_64-w64-mingw32-gcc
CPP = x86_64-w64-mingw32-g++
else
CC = gcc
CPP = g++
endif

SRC_DIR = src
BUILD_DIR = build/$(PLATFORM)
SDL_DIR = SDL

TARGET = app
ifeq ($(PLATFORM), windows)
	TARGET = app.exe
endif

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

CPP_FLAGS = -Iinclude -I$(SDL_DIR)/include  -Wall 
SDL_CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release -DSDL_STATIC=ON -DSDL_SHARED=OFF
ifeq ($(PLATFORM),windows)
    SDL_CMAKE_FLAGS += -DCMAKE_SYSTEM_NAME=Windows \
                       -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
                       -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
endif

$(BUILD_DIR)/$(TARGET): $(OBJS) $(BUILD_DIR)/SDL/libSDL3.a
	$(CPP) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CPP) -c $(CPP_FLAGS) $< -o $@

$(BUILD_DIR)/SDL/libSDL3.a:
	@mkdir -p $(BUILD_DIR)/SDL
	cd $(BUILD_DIR)/SDL && \
		cmake ../../../$(SDL_DIR) $(SDL_CMAKE_FLAGS) && \
		make -j

clean:
	rm -rf build/*.o
	rm -rf build/linux/app
	rm -rf build/windows/app.exe

.PHONY: all clean
