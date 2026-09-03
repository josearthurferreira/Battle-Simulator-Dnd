#include "animation.h"
#include "components.h"
#include "game.h"
#include "platform.h"

void MovementSystem::Update(entt ::registry &registry, float dt) {
  auto view = registry.view<Pos3Component, Speed3Component>();

  for (auto [entity, pos, spd] : view.each()) {
    pos.x += spd.x * dt;
    pos.y += spd.y * dt;
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
      anim.play("walk_side");
      p_spr.opts.hFlip = false;
    } else if (gGame->keyHeld().test(KEY_RIGHT)) {
      spd.x = 0.2;
      spd.y = 0.0;
      anim.play("walk_side");
      p_spr.opts.hFlip = true;
    } else {
      if (spd.y < 0.0) {
        anim.play("idle_up");
      } else if (spd.y > 0.0) {
        anim.play("idle_down");
      } else if (spd.x != 0.0) {
        anim.play("idle_side");
      }
      spd.x = spd.y = 0;
    }
  }
}

void RenderSystem::RenderSprites(entt::registry &registry) {
  auto view = registry.view<Pos3Component, SpriteComponent>();
  for (auto [entity, pos, spr] : view.each()) {
    spr.texture->render({pos.x, pos.y}, &spr.opts);
  }
}

void AnimationSystem::Update(entt::registry &registry, float dt) {
  auto view = registry.view<SpriteComponent, AnimatorComponent>();
  for (auto &&[entity, spr, anim] : view.each()) {
    if (!anim.currentAnimName.empty()) {
      auto &currentAnim = anim.anims[anim.currentAnimName];
      anim.update(dt);
      spr.opts.frameNum = currentAnim.frames[currentAnim.currentFrame];
    }
  }
}
