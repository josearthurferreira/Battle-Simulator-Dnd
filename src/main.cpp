#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>
#include "loader.h"
#include "battle.h"
#include "components.h"

using json = nlohmann::json;

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

    auto& spellbook = registry.emplace<SpellbookComponent>(player);
    spellbook.knownSpells.push_back("magic-missile");
    spellbook.knownSpells.push_back("fireball");

    auto& name = registry.get<NameComponent>(player).name;
    std::cout << "Grimorio de " << name << " contem:\n";

    std::ifstream spellsFile("../data/spells.json");
    json spellsData = json::parse(spellsFile);

    for (const auto& spellId : spellbook.knownSpells) {
        for (const auto& spell : spellsData) {
            if (spell["id"] == spellId) {
                std::cout << "- " << spell["name"].get<std::string>() 
                          << " (Nivel " << spell["level"].get<int>() << ", Escola: " 
                          << spell["school"].get<std::string>() << ")\n";
                
                if (spell.contains("damage_type")) {
                    std::cout << "  Dano tipo: " << spell["damage_type"].get<std::string>() << "\n";
                }
                break;
            }
        }
    }

    return 0;
}