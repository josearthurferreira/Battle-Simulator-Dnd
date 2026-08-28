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
  uint64_t init_ticks = platform_get_ticks();
  printf("Plataforma inicializada em %lu ticks\n", init_ticks);

  while (gGame->active) {
    uint64_t frame_start = platform_get_ticks();
    platform_poll_events();
    gGame->update();
    platform_begin_frame();
    gGame->render();
    platform_end_frame();
    gGame->prevKeyState = gGame->keyState;

    uint64_t dt = platform_get_ticks() - frame_start;
    printf("tempo de frame: %lu\n", dt);
  }

  delete gGame;
  destroy_platform();

  return 0;
}
