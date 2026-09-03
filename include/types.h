#ifndef INCLUDE_TYPES_H
#define INCLUDE_TYPES_H

#include <cstdint>

typedef struct {
  int x;
  int y;
} Vec2;

typedef struct {
  float x;
  float y;
} Vec2f;

typedef struct {
  int x;
  int y;
  int z;
} Vec3;

typedef struct {
  float x;
  float y;
  float z;
} Vec3f;

struct RenderOptions {
  bool hFlip;
  bool vFlip;
  float angle;
  unsigned frameNum;
};

#endif // !INCLUDE_TYPES_H
