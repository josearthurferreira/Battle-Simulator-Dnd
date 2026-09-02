#include "animation.h"

void AnimatorComponent::update(void) {
  timer += 0.1;
  while (timer >= anims[currentAnimName].frameRate) {
    anims[currentAnimName].currentFrame++;
    timer -= anims[currentAnimName].frameRate;
  }

  if (anims[currentAnimName].currentFrame ==
      anims[currentAnimName].frames.size()) {
    anims[currentAnimName].currentFrame = 0;
  }
}
void AnimatorComponent::play(std::string anim_name) {
  if (currentAnimName == anim_name) {
    return;
  }
  currentAnimName = anim_name;
  anims[currentAnimName].currentFrame = 0;
  timer = 0.0f;
}
