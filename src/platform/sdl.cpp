#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_image/SDL_image.h"
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
  font = TTF_OpenFont("../assets/macondo.ttf", 64);
  assert(font);
  printf("fonte carregada com sucesso!\n");
  win = SDL_CreateWindow("Hop", 800, 640, 0);
  assert(win);
  ren = SDL_CreateRenderer(win, NULL);
  assert(ren);
  gGame = new Game();
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

void *platform_load_img(const char *path) {
  SDL_Surface *surf = IMG_Load(path);
  assert(surf);
  const SDL_Palette *palette = SDL_GetSurfacePalette(surf);
  if (palette) {
    SDL_Color transparentColor = palette->colors[0];

    Uint32 colorKey = SDL_MapSurfaceRGB(surf, transparentColor.r,
                                        transparentColor.g, transparentColor.b);
    SDL_SetSurfaceColorKey(surf, true, colorKey);
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);

  if (!texture) {
    fprintf(stderr, "Erro ao carregar imagem '%s': %s\n", path, SDL_GetError());
  }
  assert(texture);
  SDL_DestroySurface(surf);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

  return texture;
}

void platform_render_sprite(void *data, Vec2f size, Vec2f pos, bool hFlip,
                            bool vFlip, float rot_angle, unsigned frameNum,
                            unsigned columns) {
  SDL_Texture *texture = (SDL_Texture *)data;

  float srcX = (frameNum % columns) * size.x;
  float srcY = (frameNum / columns) * size.y;

  SDL_FRect src = {srcX, srcY, size.x, size.y};
  SDL_FRect dest = {pos.x, pos.y, 5 * size.x, 5 * size.y};

  SDL_FlipMode flip = SDL_FLIP_NONE;
  if (hFlip && vFlip)
    flip = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
  else if (hFlip)
    flip = SDL_FLIP_HORIZONTAL;
  else if (vFlip)
    flip = SDL_FLIP_VERTICAL;

  SDL_RenderTextureRotated(ren, texture, &src, &dest, rot_angle, NULL, flip);
}

void platform_destroy_img(void *data) {
  SDL_DestroyTexture((SDL_Texture *)data);
}

uint64_t platform_get_ticks(void) { return SDL_GetTicks(); }

Vec2f platform_get_img_size(void *data) {
  SDL_Texture *texture = (SDL_Texture *)data;
  float w = 0, h = 0;
  if (texture) {
    SDL_GetTextureSize(texture, &w, &h);
  }
  return {w, h};
}
