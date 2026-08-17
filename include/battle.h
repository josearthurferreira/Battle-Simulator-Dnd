#ifndef INCLUDE_BATTLE_H
#define INCLUDE_BATTLE_H

#include <entt/entt.hpp>
#include <vector>

class BattleManager {
public:
    BattleManager(entt::registry& registry);
    ~BattleManager();

    void SortInitiative(entt::registry& registry);
    std::vector<entt::entity> GetTurnOrder() const;

private:
    std::vector<entt::entity> turnOrder;
};

#endif