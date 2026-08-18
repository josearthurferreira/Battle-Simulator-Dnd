#include "game.h"
#include "platform.h"

Game *gGame;

struct {
  int x;
  int y;
} PlayerPos;

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

void Game::render(void) {
  render_text(100, 100, "Manda um salve para a tropa");
  for (int i = 0; i < 25; i++) {
    draw_square(250 + 50 * (i % 5), 150 + 50 * (i / 5), 50, 50);
  }
}
