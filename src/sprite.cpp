#include "sprite.h"
#include "platform.h"

Sprite::Sprite() {}

Sprite::Sprite(const char *path, float frame_w, float frame_y) {
  data = platform_load_img(path);
}

Sprite::~Sprite(void) { platform_destroy_img(data); }

void Sprite::render(Vec2f pos) { platform_render_sprite(data, pos); }
