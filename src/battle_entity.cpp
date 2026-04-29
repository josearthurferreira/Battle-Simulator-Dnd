#include "battle.h"
#include "rng.h"
#include <algorithm>

BattleManager::BattleManager(std::vector<Character *> participants) {
  for (auto &participant : participants) {
    BattleEntity *e = new BattleEntity();
    e->character = participant;
    e->iniciative = roll_dN(20);
    entities.push_back(e);
  }

  std::sort(entities.begin(), entities.end(),
            [](BattleEntity *p1, BattleEntity *p2) {
              if (p1->iniciative == p2->iniciative) {
                return p1->character->stats[STAT_DEX] <
                       p2->character->stats[STAT_DEX];
              }
              return p1->iniciative < p2->iniciative;
            });
}

BattleManager::~BattleManager() {
  while (!entities.empty()) {
    BattleEntity *e = entities.back();
    entities.pop_back();
    delete e;
  }
}
