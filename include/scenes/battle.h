#ifndef INCLUDE_BATTLESCENE_H
#define INCLUDE_BATTLESCENE_H

#include "scene.h"

class BattleScene : public Scene {
public:
  BattleScene();

  void update() override;
  void render() override;

private:
  unsigned playerObj;
};

#endif
