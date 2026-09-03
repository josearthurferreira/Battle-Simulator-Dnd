#ifndef INCLUDE_SCENE_H
#define INCLUDE_SCENE_H

#include "entt/entt.hpp"

class Scene {
public:
  Scene();
  virtual ~Scene();
  virtual void update(float dt) = 0;
  virtual void render() = 0;

protected:
  entt::registry registry;
};

#endif
