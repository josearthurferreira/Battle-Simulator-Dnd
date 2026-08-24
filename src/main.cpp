#include "battle.h"
#include "components.h"
#include "loader.h"
#include <entt/entt.hpp>
#include <iostream>

#include "game.h"
#include "platform.h"

int main() {
  entt::registry registry;

  LoadMonsters(registry, "../data/monsters.json");

  auto view = registry.view<NameComponent, ActionsComponent>();

  for (auto entity : view) {
    auto &name = view.get<NameComponent>(entity).name;

    if (name == "Lich") {
      std::cout << "Monstro Encontrado: " << name << "\n";

      auto &actions = view.get<ActionsComponent>(entity).actions;
      std::cout << "\nAcoes de Combate:\n";
      for (const auto &act : actions) {
        std::cout << "- " << act.name << "\n";
      }

      if (registry.any_of<SpellbookComponent>(entity)) {
        auto &spellbook = registry.get<SpellbookComponent>(entity);
        std::cout << "\nFeiticos no Grimorio:\n";
        for (const auto &spellId : spellbook.knownSpells) {
          std::cout << "- " << spellId << "\n";
        }
      }
      break;
    }
  }

  init_platform();

  while (gGame->active) {
    platform_poll_events();
    gGame->update();
    platform_begin_frame();
    gGame->render();
    platform_end_frame();
    gGame->prevKeyState = gGame->keyState;
  }
  delete gGame;
  destroy_platform();

  return 0;
}
