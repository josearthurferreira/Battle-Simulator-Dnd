#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include "scene.h"
#include <bitset>

enum {
  KEY_UP = 0,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_A,
  KEY_B,
  KEY_START,
  KEY_SELECT
};

class Game {
public:
  // UP DOWN LEFT RIGHT A B START SELECT
  // W S A D Z X ENTER BACKSPACE
  std::bitset<8> keyState;
  std::bitset<8> prevKeyState;

  std::bitset<8> keyHeld();
  std::bitset<8> keyPressed();

  Game();
  ~Game();
  bool active;

  void update();
  void render();

private:
  Scene *currentScene;
};

#endif // INCLUDE_GAME_H_
