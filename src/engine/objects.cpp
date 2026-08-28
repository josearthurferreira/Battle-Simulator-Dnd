#include "objects.h"

Object::Object(const char *path, float w, float h) {
  spr = new Sprite(path, w, h);
}

Object::~Object() { delete spr; }

void Object::update() {}

void Object::render() { spr->render(pos, frameNum); }

void Object::hFlip() { spr->hFlip = !spr->hFlip; }
void Object::vFlip() { spr->vFlip = !spr->vFlip; }

bool Object::hFliped() { return spr->hFlip; }
bool Object::vFliped() { return spr->vFlip; }
void Object::rotate(float angle) { spr->rotate = angle; }
