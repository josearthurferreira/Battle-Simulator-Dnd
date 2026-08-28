#include "sprite.h"
#include "platform.h"

Sprite::Sprite() {}

Sprite::Sprite(const char *path, float frame_w, float frame_y)
    : rotate(0), hFlip(false), vFlip(false), w(frame_w), h(frame_y) {
  data = platform_load_img(path);
}

Sprite::~Sprite(void) { platform_destroy_img(data); }

void Sprite::render(Vec2f pos, unsigned frameNum) {
  platform_render_sprite(data, {w, h}, pos, hFlip, vFlip, rotate, frameNum);
}
