#ifndef INCLUDE_OBJECTS_H
#define INCLUDE_OBJECTS_H

#include "sprite.h"
#include "types.h"

class Object {
public:
  Vec2 pos;
  Vec2 size;
  Sprite *spr;

  void update();
  void render();

private:
};

#endif // !INCLUDE_OBJECTS_H
