#include "components.h"
#include "game.h"
#include "platform.h"

void MovementSystem::Update(entt ::registry &registry) {
  auto view = registry.view<Pos3Component, Speed3Component>();

  for (auto [entity, pos, spd] : view.each()) {
    pos.x += spd.x;
    pos.y += spd.y;
  }
}

void MovementSystem::PlayerInputUpdate(entt::registry &registry) {
  auto view =
      registry
          .view<Pos3Component, Speed3Component, SpriteComponent, PlayerTag>();

  for (auto [entity, pos, spd, p_spr] : view.each()) {
    if (gGame->keyHeld().test(KEY_UP)) {
      spd.x = 0.0;
      spd.y = -0.2;
      p_spr.opts.frameNum = 1;
    } else if (gGame->keyHeld().test(KEY_DOWN)) {
      spd.x = 0.0;
      spd.y = 0.2;
      p_spr.opts.frameNum = 0;
    } else if (gGame->keyHeld().test(KEY_LEFT)) {
      spd.x = -0.2;
      spd.y = 0.0;
      p_spr.opts.frameNum = 2;
      p_spr.opts.hFlip = false;
    } else if (gGame->keyHeld().test(KEY_RIGHT)) {
      spd.x = 0.2;
      spd.y = 0.0;
      p_spr.opts.frameNum = 2;
      p_spr.opts.hFlip = true;
    } else {
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
