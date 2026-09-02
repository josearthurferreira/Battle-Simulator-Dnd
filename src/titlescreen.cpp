#include "scenes/titlescreen.h"
#include "game.h"
#include "platform.h"
#include "scenes/battle.h"

TitleScreen::TitleScreen() {}

void TitleScreen::update() {
  if (gGame->keyPressed().test(KEY_START)) {
    gGame->changeScene(new BattleScene());
    return;
  }
}

void TitleScreen::render() {
  render_text(120, 75, "SIMULADOR DE COMBATE", 64.0f);
}
