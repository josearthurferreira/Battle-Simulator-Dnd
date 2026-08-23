#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game.h"
#include "platform.h"
#include <cassert>
#include <cstdlib>

SDL_Window *win;
SDL_Renderer *ren;
TTF_Font *font;

void init_platform(void) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  font = TTF_OpenFont("assets/macondo.ttf", 64);
  if (font) {
    printf("fonte carregada com sucesso!\n");
  }
  win = SDL_CreateWindow("Hop", 800, 640, 0);
  assert(win);
  ren = SDL_CreateRenderer(win, NULL);
  assert(ren);
  gGame->active = true;
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
    switch (e.type) {
    case SDL_EVENT_QUIT:
      gGame->active = false;
      break;

    case SDL_EVENT_KEY_DOWN:
      if (e.key.repeat)
        break;
      switch (e.key.key) {
      case SDLK_W:
        gGame->keyState.set(0);
        break; // UP
      case SDLK_S:
        gGame->keyState.set(1);
        break; // DOWN
      case SDLK_A:
        gGame->keyState.set(2);
        break; // LEFT
      case SDLK_D:
        gGame->keyState.set(3);
        break; // RIGHT
      case SDLK_Z:
        gGame->keyState.set(4);
        break; // A
      case SDLK_X:
        gGame->keyState.set(5);
        break; // B
      case SDLK_RETURN:
        gGame->keyState.set(6);
        break; // START
      case SDLK_BACKSPACE:
        gGame->keyState.set(7);
        break; // SELECT
      }
      break;

    case SDL_EVENT_KEY_UP:
      switch (e.key.key) {
      case SDLK_W:
        gGame->keyState.reset(0);
        break;
      case SDLK_S:
        gGame->keyState.reset(1);
        break;
      case SDLK_A:
        gGame->keyState.reset(2);
        break;
      case SDLK_D:
        gGame->keyState.reset(3);
        break;
      case SDLK_Z:
        gGame->keyState.reset(4);
        break;
      case SDLK_X:
        gGame->keyState.reset(5);
        break;
      case SDLK_RETURN:
        gGame->keyState.reset(6);
        break;
      case SDLK_BACKSPACE:
        gGame->keyState.reset(7);
        break;
      }
      break;
    }
  }
}

void draw_square(int x, int y, int w, int h) {
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 1);
  SDL_FRect r = {.x = static_cast<float>(x),
                 .y = static_cast<float>(y),
                 .w = static_cast<float>(w),
                 .h = static_cast<float>(h)};

  SDL_RenderRect(ren, &r);
}

void render_text(int x, int y, const char *text, float size) {
  if (!text || !font || !ren)
    return;

  SDL_Color color = {0, 0, 0, 255};
  SDL_Surface *surf = TTF_RenderText_Blended(font, text, strlen(text), color);
  if (!surf) {
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);

  SDL_DestroySurface(surf);

  if (!texture) {
    return;
  }

  float tex_w, tex_h;
  SDL_GetTextureSize(texture, &tex_w, &tex_h);

  SDL_FRect src = {0, 0, tex_w, tex_h};
  SDL_FRect dest = {(float)x, (float)y, tex_w * size / tex_h, size};

  SDL_RenderTexture(ren, texture, &src, &dest);
  SDL_DestroyTexture(texture);
}
