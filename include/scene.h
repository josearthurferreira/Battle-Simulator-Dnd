#ifndef INCLUDE_SCENE_H
#define INCLUDE_SCENE_H

#include "objects.h"
#include <memory>
#include <vector>

class Scene {
public:
  Scene();
  virtual ~Scene();
  virtual void update();
  virtual void render();

  unsigned createObj(const char *path, float w, float h);
  void deleteObj(unsigned id);

protected:
  std::vector<std::unique_ptr<Object>> objs;
  unsigned nObjs;
};

#endif
