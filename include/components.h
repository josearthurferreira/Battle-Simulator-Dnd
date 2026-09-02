#ifndef INCLUDE_COMPONENTS_H
#define INCLUDE_COMPONENTS_H

#include "entt/entt.hpp"
#include "sprite.h"
#include "types.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

enum Stats : uint8_t {
  STAT_STR,
  STAT_DEX,
  STAT_CON,
  STAT_INT,
  STAT_WIS,
  STAT_CHA,
  STAT_TOTAL
};

struct NameComponent {
  std::string name;
};

struct AttributesComponent {
  unsigned int stats[STAT_TOTAL];
};

struct PlayerProgressionComponent {
  unsigned int exp;
  std::unordered_map<std::string, int> classLevels;
};

struct MonsterDataComponent {
  std::string type;
  float challengeRating;
};

struct CombatStateComponent {
  int currentHP;
  int maxHP;
  int initiativeRoll;
};

struct SpeedComponent {
  int speed;
};

struct TraitsComponent {
  std::vector<std::string> traits;
};

struct ProficienciesComponent {
  std::vector<std::string> proficiencies;
};

struct SpellbookComponent {
  std::vector<std::string> knownSpells;
};

struct Action {
  std::string name;
  std::string description;
};

struct ActionsComponent {
  std::vector<Action> actions;
};

struct Pos3Component {
  float x;
  float y;
  float z;
};

struct Speed3Component {
  float x;
  float y;
  float z;
};

struct SpriteComponent {
  std::shared_ptr<Sprite> texture;
  RenderOptions opts;
};

struct PlayerTag {};

namespace MovementSystem {
void PlayerInputUpdate(entt::registry &registry);
void Update(entt ::registry &registry);
}; // namespace MovementSystem

namespace RenderSystem {
void RenderSprites(entt::registry &reg);
}

#endif
