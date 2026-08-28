#include "game.h"
#include "platform.h"
#include "titlescreen.h"

Game *gGame;

Game::Game() { currentScene = new TitleScreen(); }

Game::~Game() { delete currentScene; }

void Game::update(void) { currentScene->update(); }

void Game::render(void) { currentScene->render(); }

std::bitset<8> Game::keyHeld() { return keyState & prevKeyState; }

std::bitset<8> Game::keyPressed() { return keyState & ~prevKeyState; }
