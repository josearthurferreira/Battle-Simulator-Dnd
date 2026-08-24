#include "objects.h"

Object::Object(const char *path, float w, float h) {
  spr = new Sprite(path, w, h);
}

Object::~Object() { delete spr; }

void Object::update() {}

void Object::render() { spr->render(pos); }

void Object::hFlip() { spr->hFlip = !spr->hFlip; }
void Object::vFlip() { spr->vFlip = !spr->vFlip; }
void Object::rotate(float angle) { spr->rotate = angle; }
