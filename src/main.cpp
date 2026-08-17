#include <iostream>
#include <entt/entt.hpp>
#include "loader.h"
#include "battle.h"
#include "components.h"

int main() {
    entt::registry registry;

    LoadMonsters(registry, "../data/monsters.json");

    auto view = registry.view<NameComponent, ActionsComponent>();
    
    for(auto entity : view) {
        auto& name = view.get<NameComponent>(entity).name;
        
        if(name == "Lich") {
            std::cout << "Monstro Encontrado: " << name << "\n";
            
            auto& actions = view.get<ActionsComponent>(entity).actions;
            std::cout << "\nAcoes de Combate:\n";
            for(const auto& act : actions) {
                std::cout << "- " << act.name << "\n";
            }

            if(registry.any_of<SpellbookComponent>(entity)) {
                auto& spellbook = registry.get<SpellbookComponent>(entity);
                std::cout << "\nFeiticos no Grimorio:\n";
                for(const auto& spellId : spellbook.knownSpells) {
                    std::cout << "- " << spellId << "\n";
                }
            }
            break; 
        }
    }

    return 0;
}