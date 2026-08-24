#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

#include "types.h"

class Sprite {
public:
  Sprite();
  Sprite(const char *path, float frame_w, float frame_h);
  ~Sprite();
  void update(void);
  void render(Vec2f pos);

  friend class Object;

private:
  void *data;
  float w, h;
  bool hFlip, vFlip;
  float rotate;
};

#endif // INCLUDE_SPRITE_H_
