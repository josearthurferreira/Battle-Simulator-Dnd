#include <iostream>
#include <entt/entt.hpp>
#include "loader.h"
#include "battle.h"
#include "components.h"

int main() {
    entt::registry registry;

    LoadMonsters(registry, "../data/monsters.json");

    BattleManager battleManager(registry);

    auto turnOrder = battleManager.GetTurnOrder();
    
    std::cout << "Ordem de Turnos Carregada:\n";
    for (auto entity : turnOrder) {
        auto& name = registry.get<NameComponent>(entity).name;
        auto& combatState = registry.get<CombatStateComponent>(entity);
        std::cout << "- " << name << " (HP: " << combatState.currentHP << ")\n";
    }

    return 0;
}