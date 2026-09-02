#include "animation.h"
#include "components.h"
#include "game.h"
#include "loader.h"
#include "platform.h"
#include "scenes/battle.h"

extern Game *gGame;

BattleScene::BattleScene() {
  entt::entity player = LoadAnimator(registry, "../assets/character.json");
  registry.emplace<PlayerTag>(player);
  registry.emplace<Pos3Component>(player, 100.0f, 100.0f, 100.0f);
  registry.emplace<Speed3Component>(player, 0.0f, 0.0f, 0.0f);

  entt::entity player2 = LoadAnimator(registry, "../assets/character2.json");
  registry.emplace<PlayerTag>(player2);
  registry.emplace<Pos3Component>(player2, 200.0f, 200.0f, 100.0f);
  registry.emplace<Speed3Component>(player2, 0.0f, 0.0f, 0.0f);
}

void BattleScene::update() {
  MovementSystem::PlayerInputUpdate(registry);
  MovementSystem::Update(registry);
  AnimationSystem::Update(registry);
}

void BattleScene::render() {
  for (int j = 0; j < 25; j++) {
    draw_square(250 + 50 * (j % 5), 150 + 50 * (j / 5), 50, 50);
  }
  RenderSystem::RenderSprites(registry);
}
