#include "game.h"
#include "platform.h"

int main(int argc, char const *argv[]) {
  gGame = new Game();
  init_platform();

  while (gGame->active) {
    platform_poll_events();
    gGame->update();
    platform_begin_frame();
    gGame->render();
    platform_end_frame();
  }
  delete gGame;
  destroy_platform();
  return 0;
}
