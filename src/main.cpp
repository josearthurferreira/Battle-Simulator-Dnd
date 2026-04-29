#include "platform.h"

void game_update(void) {}
void game_render(void) {}

bool game_active = false;

int main(int argc, char const *argv[]) {
  init_platform();

  while (game_active) {
    platform_poll_events();
    game_update();
    platform_begin_frame();
    game_render();
    platform_end_frame();
  }

  destroy_platform();
  return 0;
}
