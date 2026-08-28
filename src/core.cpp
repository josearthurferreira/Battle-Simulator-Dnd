#include "game.h"
#include "objects.h"
#include "platform.h"

Game *gGame;
Object *obj = nullptr;

int i = 0;

Game::Game() {
  obj = new Object("../assets/character.png", 16, 32);
  obj->pos = {100, 100};
  obj->frameNum = 0;
}

Game::~Game() {}

void Game::update(void) {
  if (keyHeld().test(KEY_UP)) {
    obj->pos.y -= 0.2;
    obj->frameNum = 1;
  } else if (keyHeld().test(KEY_DOWN)) {
    obj->pos.y += 0.2;
    obj->frameNum = 0;
  } else if (keyHeld().test(KEY_LEFT)) {
    obj->pos.x -= 0.2;
    obj->frameNum = 2;
    if (obj->hFliped())
      obj->hFlip();
  } else if (keyHeld().test(KEY_RIGHT)) {
    obj->pos.x += 0.2;
    obj->frameNum = 2;
    if (!obj->hFliped())
      obj->hFlip();
  }

  obj->update();
}

void Game::render(void) {
  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
  obj->render();
  render_text(100, 100, "Manda um salve para a tropa", 30.0f);
}

std::bitset<8> Game::keyHeld() { return keyState & prevKeyState; }

std::bitset<8> Game::keyPressed() { return keyState & ~prevKeyState; }
