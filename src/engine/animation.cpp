#include "animation.h"

void AnimatorComponent::update(float dt) {
  timer += dt;
  if (currentAnimName.empty()) {
    return;
  }
  auto &anim = anims[currentAnimName];
  while (timer >= anim.frameRate) {
    anim.currentFrame++;
    timer -= anim.frameRate;
  }

  if (anim.currentFrame >= anim.frames.size()) {
    anim.currentFrame = anim.currentFrame % anim.frames.size();
  }
}

void AnimatorComponent::play(std::string anim_name) {
  if (currentAnimName == anim_name || !anims.contains(anim_name)) {
    return;
  }
  currentAnimName = anim_name;
  anims[currentAnimName].currentFrame = 0;
  timer = 0.0f;
}

void AnimatorComponent::stop() {
  currentAnimName = "";
  timer = 0.0f;
}
