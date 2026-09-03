#include "entt/entt.hpp"
#include <map>
#include <string>

struct AnimationClip {
  std::vector<unsigned> frames;
  unsigned currentFrame;
  float frameRate;
};

struct AnimatorComponent {
  std::string currentAnimName;
  std::map<std::string, AnimationClip> anims;
  float timer;

  void play(std::string anim_name);
  void update(float dt);
};

entt::entity createAnimator(const char *fpath);

namespace AnimationSystem {
void Update(entt::registry &registry, float dt);
}
