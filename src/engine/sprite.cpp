#include "sprite.h"
#include "platform.h"

Sprite::Sprite() {}

Sprite::Sprite(const char *path, float frame_w, float frame_y)
    : w(frame_w), h(frame_y) {
  data = platform_load_img(path);
  Vec2f sizes = platform_get_img_size(data);
  nColumns = sizes.x / frame_w;
}

Sprite::~Sprite(void) { platform_destroy_img(data); }

void Sprite::render(Vec2f pos, RenderOptions *options) {
  platform_render_sprite(data, {w, h}, pos, options->hFlip, options->vFlip,
                         options->angle, options->frameNum, nColumns);
}
