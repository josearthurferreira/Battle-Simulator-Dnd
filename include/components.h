#ifndef INCLUDE_COMPONENTS_H
#define INCLUDE_COMPONENTS_H

#include <string>
#include <cstdint>
#include <unordered_map>

enum Stats : uint8_t { STAT_STR, STAT_DEX, STAT_CON, STAT_INT, STAT_WIS, STAT_CHA, STAT_TOTAL };

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
    std::string species;
    float challengeRating;
};

struct CombatStateComponent {
    int currentHP;
    int maxHP;
    int initiativeRoll;
};

#endif