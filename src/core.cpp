#include "game.h"
#include "platform.h"

Game *gGame;

int i = 0;

struct {
  int x;
  int y;
} PlayerPos;

Game::Game() {}
Game::~Game() {}

void Game::update(void) {
  if (keyState.test(KEY_UP)) {
    PlayerPos.y--;
  }
  if (keyState.test(KEY_DOWN)) {
    PlayerPos.y++;
  }
  if (keyState.test(KEY_LEFT)) {
    PlayerPos.x--;
  }
  if (keyState.test(KEY_RIGHT)) {
    PlayerPos.x++;
  }
}

#include <math.h>

void Game::render(void) {
  render_text(100, 100, "Manda um salve para a tropa", 30.0f);

  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
}
