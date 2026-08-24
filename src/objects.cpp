#include "objects.h"

Object::Object(const char *path, float w, float h) {
  spr = new Sprite(path, w, h);
}

Object::~Object() { delete spr; }

void Object::update() {}

void Object::render() { spr->render(pos); }
