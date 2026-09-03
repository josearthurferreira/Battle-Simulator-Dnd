#include "loader.h"
#include "animation.h"
#include "components.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void LoadMonsters(entt::registry &registry, const std::string &filepath) {
  std::ifstream file(filepath);
  json data = json::parse(file);

  for (const auto &item : data) {
    auto entity = registry.create();

    registry.emplace<NameComponent>(entity, item["name"].get<std::string>());

    registry.emplace<MonsterDataComponent>(
        entity, item["type"].get<std::string>(), item["cr"].get<float>());

    registry.emplace<CombatStateComponent>(entity, item["hp"].get<int>(),
                                           item["hp"].get<int>(), 0);

    auto &attrs = registry.emplace<AttributesComponent>(entity);
    auto statsArray = item["attributes"].get<std::vector<unsigned int>>();
    for (int i = 0; i < STAT_TOTAL; ++i) {
      attrs.stats[i] = statsArray[i];
    }

    auto &actionsComp = registry.emplace<ActionsComponent>(entity);
    for (const auto &act : item["actions"]) {
      actionsComp.actions.push_back(
          {act["name"].get<std::string>(), act["desc"].get<std::string>()});
    }

    auto spellsArray = item["spells"].get<std::vector<std::string>>();
    if (!spellsArray.empty()) {
      auto &spellbook = registry.emplace<SpellbookComponent>(entity);
      spellbook.knownSpells = spellsArray;
    }
  }
}

entt::entity CreatePlayer(entt::registry &registry, const std::string &name,
                          const std::string &raceId,
                          const std::string &subraceId,
                          const std::string &backgroundId,
                          const std::vector<unsigned int> &baseStats,
                          const std::string &racesFilepath,
                          const std::string &subracesFilepath,
                          const std::string &backgroundsFilepath) {
  auto entity = registry.create();
  registry.emplace<NameComponent>(entity, name);

  std::ifstream racesFile(racesFilepath);
  json racesData = json::parse(racesFile);

  json selectedRace;
  for (const auto &race : racesData) {
    if (race["id"] == raceId) {
      selectedRace = race;
      break;
    }
  }

  json selectedSubrace;
  if (!subraceId.empty()) {
    std::ifstream subracesFile(subracesFilepath);
    if (subracesFile.is_open()) {
      json subracesData = json::parse(subracesFile);
      for (const auto &subrace : subracesData) {
        if (subrace["id"] == subraceId) {
          selectedSubrace = subrace;
          break;
        }
      }
    }
  }

  auto &attrs = registry.emplace<AttributesComponent>(entity);
  auto raceBonuses =
      selectedRace["ability_bonuses"].get<std::vector<unsigned int>>();

  std::vector<unsigned int> subraceBonuses(STAT_TOTAL, 0);
  if (!selectedSubrace.empty()) {
    subraceBonuses =
        selectedSubrace["ability_bonuses"].get<std::vector<unsigned int>>();
  }

  for (int i = 0; i < STAT_TOTAL; ++i) {
    attrs.stats[i] = baseStats[i] + raceBonuses[i] + subraceBonuses[i];
  }

  registry.emplace<SpeedComponent>(entity, selectedRace["speed"].get<int>());

  auto &traits = registry.emplace<TraitsComponent>(entity);
  traits.traits = selectedRace["traits"].get<std::vector<std::string>>();

  if (!selectedSubrace.empty()) {
    auto subTraits = selectedSubrace["traits"].get<std::vector<std::string>>();
    traits.traits.insert(traits.traits.end(), subTraits.begin(),
                         subTraits.end());
  }

  auto &proficiencies = registry.emplace<ProficienciesComponent>(entity);
  auto raceProfs =
      selectedRace["starting_proficiencies"].get<std::vector<std::string>>();
  proficiencies.proficiencies.insert(proficiencies.proficiencies.end(),
                                     raceProfs.begin(), raceProfs.end());

  if (!selectedSubrace.empty()) {
    auto subProfs = selectedSubrace["starting_proficiencies"]
                        .get<std::vector<std::string>>();
    proficiencies.proficiencies.insert(proficiencies.proficiencies.end(),
                                       subProfs.begin(), subProfs.end());
  }

  std::ifstream bgsFile(backgroundsFilepath);
  json bgsData = json::parse(bgsFile);

  for (const auto &bg : bgsData) {
    if (bg["id"] == backgroundId) {
      auto bgProfs =
          bg["starting_proficiencies"].get<std::vector<std::string>>();
      proficiencies.proficiencies.insert(proficiencies.proficiencies.end(),
                                         bgProfs.begin(), bgProfs.end());
      break;
    }
  }

  registry.emplace<PlayerProgressionComponent>(
      entity, 0u, std::unordered_map<std::string, int>());
  registry.emplace<CombatStateComponent>(entity, 10, 10, 0);

  return entity;
}

entt::entity LoadAnimator(entt::registry &registry, const char *fpath) {
  std::ifstream fstr(fpath);
  json animData = json::parse(fstr);

  entt::entity e = registry.create();
  std::shared_ptr<Sprite> spr = std::make_shared<Sprite>(
      animData["sheet"].get<std::string>().c_str(),
      animData["width"].get<float>(), animData["height"].get<float>());
  RenderOptions opts = {false, false, 0, 0, 0};
  registry.emplace<SpriteComponent>(e, spr, opts);
  auto &anim = registry.emplace<AnimatorComponent>(e);

  for (auto &[clipName, clipData] : animData["animations"].items()) {
    AnimationClip clip;
    clip.frames = clipData["frames"].get<std::vector<unsigned>>();
    clip.frameRate = clipData.value("frameRate", 0.5f);

    anim.anims[clipName] = clip;
  }

  return e;
}
