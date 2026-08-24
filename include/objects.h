#ifndef INCLUDE_OBJECTS_H
#define INCLUDE_OBJECTS_H

#include "sprite.h"
#include "types.h"

class Object {
public:
  Object(const char *, float w, float h);
  ~Object();
  Vec2f pos;
  Vec2f size;

  void update();
  void render();

private:
  Sprite *spr;
};

#endif // !INCLUDE_OBJECTS_H
