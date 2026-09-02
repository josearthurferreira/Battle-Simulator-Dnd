#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

#include "types.h"

class Sprite {
public:
  Sprite();
  Sprite(const char *path, float frame_w, float frame_h);
  ~Sprite();

  void render(Vec2f pos, RenderOptions *options);

private:
  void *data;
  float w, h;
};

#endif // INCLUDE_SPRITE_H_
