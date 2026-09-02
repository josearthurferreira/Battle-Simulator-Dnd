#ifndef INCLUDE_LOADER_H
#define INCLUDE_LOADER_H

#include <entt/entt.hpp>
#include <string>
#include <vector>

void LoadMonsters(entt::registry &registry, const std::string &filepath);
entt::entity CreatePlayer(entt::registry &registry, const std::string &name,
                          const std::string &raceId,
                          const std::string &subraceId,
                          const std::string &backgroundId,
                          const std::vector<unsigned int> &baseStats,
                          const std::string &racesFilepath,
                          const std::string &subracesFilepath,
                          const std::string &backgroundsFilepath);
entt::entity LoadAnimator(entt::registry &registry, const char *fpath);

#endif
