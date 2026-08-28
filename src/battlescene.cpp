#include "game.h"
#include "platform.h"
#include "scenes/battle.h"

extern Game *gGame;

BattleScene::BattleScene() {
  playerObj = createObj("../assets/character.png", 16, 32);
  objs[playerObj]->pos = {100, 100};
  objs[playerObj]->frameNum = 0;
}

void BattleScene::update() {
#define obj objs[playerObj]
  if (gGame->keyHeld().test(KEY_UP)) {
    obj->pos.y -= 0.2;
    obj->frameNum = 1;
  } else if (gGame->keyHeld().test(KEY_DOWN)) {
    obj->pos.y += 0.2;
    obj->frameNum = 0;
  } else if (gGame->keyHeld().test(KEY_LEFT)) {
    obj->pos.x -= 0.2;
    obj->frameNum = 2;
    if (obj->hFliped())
      obj->hFlip();
  } else if (gGame->keyHeld().test(KEY_RIGHT)) {
    obj->pos.x += 0.2;
    obj->frameNum = 2;
    if (!obj->hFliped())
      obj->hFlip();
  }

  Scene::update();
#undef obj
}

void BattleScene::render() {
  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
  Scene::render();
}
