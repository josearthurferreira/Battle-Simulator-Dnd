#include "components.h"
#include "game.h"
#include "platform.h"
#include "scenes/battle.h"
#include <memory>

extern Game *gGame;

BattleScene::BattleScene() {
  entt::entity player = registry.create();
  registry.emplace<PlayerTag>(player);
  registry.emplace<Pos3Component>(player, 100.0f, 100.0f, 100.0f);
  registry.emplace<Speed3Component>(player, 0.0f, 0.0f, 0.0f);
  std::shared_ptr<Sprite> texture =
      std::make_shared<Sprite>("../assets/character.png", 16, 32);
  RenderOptions opts = {false, false, 0, 0, 0};
  registry.emplace<SpriteComponent>(player, texture, opts);
}

void BattleScene::update() {
  MovementSystem::PlayerInputUpdate(registry);
  MovementSystem::Update(registry);
}

void BattleScene::render() {
  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
  RenderSystem::RenderSprites(registry);
}
