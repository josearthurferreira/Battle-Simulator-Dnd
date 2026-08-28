#include "titlescreen.h"
#include "game.h"
#include "platform.h"
#include "scene.h"

TitleScreen::TitleScreen() {
  playerObj = createObj("../assets/character.png", 16, 32);
  objs[playerObj]->pos = {100, 100};
  objs[playerObj]->frameNum = 0;
}

void TitleScreen::update() {
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

void TitleScreen::render() {
  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
  render_text(100, 100, "Manda um salve para a tropa", 30.0f);

  Scene::render();
}
