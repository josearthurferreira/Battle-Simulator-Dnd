#ifndef INCLUDE_TITLESCREEN_H_
#define INCLUDE_TITLESCREEN_H_

#include "scene.h"

class TitleScreen : public Scene {
public:
  TitleScreen();

  void update() override;
  void render() override;

private:
  unsigned playerObj;
};

#endif // INCLUDE_TITLESCREEN_H_
