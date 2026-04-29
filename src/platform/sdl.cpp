#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "platform.h"
#include <cassert>
#include <cstdlib>

SDL_Window *win;
SDL_Renderer *ren;
extern bool game_active;

void init_platform(void) {
  SDL_Init(SDL_INIT_VIDEO);
  win = SDL_CreateWindow("Hop", 800, 640, 0);
  assert(win);
  ren = SDL_CreateRenderer(win, NULL);
  assert(ren);
  game_active = true;
}

void destroy_platform(void) {
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

void platform_begin_frame(void) {
  SDL_SetRenderDrawColor(ren, 0XFF, 0xff, 0xff, 1);
  SDL_RenderClear(ren);
}

void platform_end_frame(void) { SDL_RenderPresent(ren); }

void platform_poll_events(void) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      game_active = false;
    }
  }
}
