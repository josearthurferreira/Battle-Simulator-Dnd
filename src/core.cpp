#include "game.h"
#include "objects.h"
#include "platform.h"
#include "titlescreen.h"

Game *gGame;
Object *obj = nullptr;

int i = 0;

Game::Game() { currentScene = new TitleScreen(); }

Game::~Game() { delete obj; }

void Game::update(void) { currentScene->update(); }

void Game::render(void) { currentScene->render(); }

std::bitset<8> Game::keyHeld() { return keyState & prevKeyState; }

std::bitset<8> Game::keyPressed() { return keyState & ~prevKeyState; }
