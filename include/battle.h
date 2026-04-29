#ifndef INCLUDE_BATTLE_H
#define INCLUDE_BATTLE_H

#include "character.h"
#include <cstdint>
#include <vector>

enum BoardState : uint8_t {
  FREE_SPACE,
  PLAYER_SPACE,
  ENEMY_SPACE,
};

class BattleEntity {
public:
  Character *character;
  uint8_t iniciative;
  std::pair<uint8_t, uint8_t> pos;
};

class BattleManager {
public:
  BattleManager(std::vector<Character *> participants);
  ~BattleManager();
  std::vector<BattleEntity *> entities;

private:
};

void startBattle(void);

#endif
