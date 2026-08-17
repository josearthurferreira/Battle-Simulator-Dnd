#include "loader.h"
#include "components.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void LoadMonsters(entt::registry& registry, const std::string& filepath) {
    std::ifstream file(filepath);
    json data = json::parse(file);

    for (const auto& item : data) {
        auto entity = registry.create();

        registry.emplace<NameComponent>(entity, item["name"].get<std::string>());
        
        registry.emplace<MonsterDataComponent>(entity, 
            item["species"].get<std::string>(), 
            item["cr"].get<float>()
        );

        registry.emplace<CombatStateComponent>(entity, 
            item["hp"].get<int>(), 
            item["hp"].get<int>(), 
            0
        );

        auto& attrs = registry.emplace<AttributesComponent>(entity);
        auto statsArray = item["attributes"].get<std::vector<unsigned int>>();
        for (int i = 0; i < STAT_TOTAL; ++i) {
            attrs.stats[i] = statsArray[i];
        }
    }
}