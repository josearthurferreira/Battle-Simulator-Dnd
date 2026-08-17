#include "battle.h"
#include "components.h"

BattleManager::BattleManager(entt::registry& registry) {
    auto view = registry.view<CombatStateComponent>();
    for(auto entity : view) {
        turnOrder.push_back(entity);
    }
    SortInitiative(registry);
}

BattleManager::~BattleManager() {
    turnOrder.clear();
}

void BattleManager::SortInitiative(entt::registry& registry) {
    registry.sort<CombatStateComponent>([](const auto& lhs, const auto& rhs) {
        return lhs.initiativeRoll > rhs.initiativeRoll;
    });

    turnOrder.clear();
    auto view = registry.view<CombatStateComponent>();
    for(auto entity : view) {
        turnOrder.push_back(entity);
    }
}

std::vector<entt::entity> BattleManager::GetTurnOrder() const {
    return turnOrder;
}