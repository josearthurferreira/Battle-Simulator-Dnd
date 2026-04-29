TARGET_PLATFORM ?= linux
VIDEO_BACKEND ?= sdl

ifeq ($(PLATFORM), windows)
CC = x86_64-w64-mingw32-gcc
CPP = x86_64-w64-mingw32-g++
else
CC = gcc
CPP = g++
endif

SRC_DIR = src
BUILD_DIR = build/$(TARGET_PLATFORM)/$(VIDEO_BACKEND)
SDL_DIR = SDL

ifeq ($(TARGET_PLATFORM), windows)
	TARGET = app.exe
else ifeq ($(TARGET_PLATFORM), linux)
	TARGET = app
else
	$(error Target inválido: $(TARGET_PLATFORM))
endif


CPP_FLAGS = -Iinclude -Wall 
SDL_CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release -DSDL_STATIC=ON -DSDL_SHARED=OFF

ifeq ($(PLATFORM),windows)
    SDL_CMAKE_FLAGS += -DCMAKE_SYSTEM_NAME=Windows \
                       -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
                       -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++
endif

ifeq ($(VIDEO_BACKEND), sdl)
    PLATFORM_SRCS := src/platform/sdl.cpp
    CPP_FLAGS += -I$(SDL_DIR)/include
    LDFLAGS += $(BUILD_DIR)/SDL/libSDL3.a
else ifeq ($(VIDEO_BACKEND), framebuffer)
    PLATFORM_SRCS := src/platform/framebuffer.cpp
else
    $(error Backend inválido: $(VIDEO_BACKEND))
endif


COMMON_SRCS := $(shell find src -name '*.cpp' ! -path 'src/platform/*')
SRCS := $(COMMON_SRCS) $(PLATFORM_SRCS)
OBJS := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(BUILD_DIR)/$(TARGET): $(OBJS) $(BUILD_DIR)/SDL/libSDL3.a
	$(CPP) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(BUILD_DIR)/SDL/libSDL3.a:
	@mkdir -p $(BUILD_DIR)/SDL
	cd $(BUILD_DIR)/SDL && \
		cmake ../../../../$(SDL_DIR) $(SDL_CMAKE_FLAGS) && \
		make -j

clean:
	rm -rf build/*.o
	rm -rf build/linux/app
	rm -rf build/windows/app.exe

.PHONY: all clean
