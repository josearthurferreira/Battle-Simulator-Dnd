#include <iostream>
#include <entt/entt.hpp>
#include "loader.h"
#include "battle.h"
#include "components.h"

int main() {
    entt::registry registry;

    std::vector<unsigned int> baseStats = {15, 14, 13, 12, 10, 8};
    
    entt::entity player = CreatePlayer(
        registry, 
        "Tharivol", 
        "elf", 
        "high-elf", 
        "acolyte", 
        baseStats, 
        "../data/races.json", 
        "../data/subraces.json", 
        "../data/backgrounds.json"
    );

    auto& name = registry.get<NameComponent>(player).name;
    auto& attrs = registry.get<AttributesComponent>(player);
    
    std::cout << "Personagem: " << name << "\n";
    std::cout << "DEX base 14 + racial -> Final: " << attrs.stats[STAT_DEX] << "\n";
    std::cout << "INT base 12 + subracial -> Final: " << attrs.stats[STAT_INT] << "\n\n";

    auto& traits = registry.get<TraitsComponent>(player);
    std::cout << "Tracos Adquiridos:\n";
    for (const auto& t : traits.traits) {
        std::cout << "- " << t << "\n";
    }

    return 0;
}