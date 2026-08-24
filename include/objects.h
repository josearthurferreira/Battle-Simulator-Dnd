#ifndef INCLUDE_OBJECTS_H
#define INCLUDE_OBJECTS_H

#include "sprite.h"
#include "types.h"
#include <cstdint>

class Object {
public:
  Object(const char *, float w, float h);
  ~Object();
  Vec2f pos;
  Vec2f size;

  void hFlip();
  void vFlip();
  void rotate(float angle);

  void update();
  void render();

private:
  Sprite *spr;
  uint8_t data_bytes[4];
};

#endif // !INCLUDE_OBJECTS_H
