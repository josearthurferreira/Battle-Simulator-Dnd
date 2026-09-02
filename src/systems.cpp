#include "animation.h"
#include "components.h"
#include "game.h"
#include "platform.h"
#include <iostream>

void MovementSystem::Update(entt ::registry &registry) {
  auto view = registry.view<Pos3Component, Speed3Component>();

  for (auto [entity, pos, spd] : view.each()) {
    pos.x += spd.x;
    pos.y += spd.y;
  }
}

void MovementSystem::PlayerInputUpdate(entt::registry &registry) {
  auto view = registry.view<Pos3Component, Speed3Component, SpriteComponent,
                            AnimatorComponent, PlayerTag>();

  for (auto &&[entity, pos, spd, p_spr, anim] : view.each()) {
    if (gGame->keyHeld().test(KEY_UP)) {
      spd.x = 0.0;
      spd.y = -0.2;
      anim.play("walk_up");
    } else if (gGame->keyHeld().test(KEY_DOWN)) {
      spd.x = 0.0;
      spd.y = 0.2;
      anim.play("walk_down");
    } else if (gGame->keyHeld().test(KEY_LEFT)) {
      spd.x = -0.2;
      spd.y = 0.0;
      anim.play("walk_left");
      p_spr.opts.hFlip = false;
    } else if (gGame->keyHeld().test(KEY_RIGHT)) {
      spd.x = 0.2;
      spd.y = 0.0;
      anim.play("walk_right");
      p_spr.opts.hFlip = true;
    } else {
      spd.x = spd.y = 0;
      anim.play("idle");
    }
  }
}

void RenderSystem::RenderSprites(entt::registry &registry) {
  auto view = registry.view<Pos3Component, SpriteComponent>();
  for (auto [entity, pos, spr] : view.each()) {
    spr.texture->render({pos.x, pos.y}, &spr.opts);
  }
}

void AnimationSystem::Update(entt::registry &registry) {
  auto view = registry.view<SpriteComponent, AnimatorComponent>();
  for (auto &&[entity, spr, anim] : view.each()) {
    if (!anim.currentAnimName.empty()) {
      auto &currentAnim = anim.anims[anim.currentAnimName];
      std::cout << anim.currentAnimName << " " << currentAnim.currentFrame
                << std::endl;
      anim.update();
      spr.opts.frameNum = currentAnim.frames[currentAnim.currentFrame];
    }
  }
}
