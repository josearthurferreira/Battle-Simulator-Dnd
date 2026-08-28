#include "scene.h"

Scene::Scene() { nObjs = 0; }

Scene::~Scene() {
  for (auto it = objs.begin(); it != objs.end(); it++) {
    (void)it->release();
    nObjs--;
  }
}

void Scene::update() {
  for (auto it = objs.begin(); it != objs.end(); it++) {
    (*it)->update();
  }
}

void Scene::render() {
  for (auto it = objs.begin(); it != objs.end(); it++) {
    (*it)->render();
  }
}

unsigned Scene::createObj(const char *path, float w, float h) {
  std::unique_ptr<Object> ptr = std::make_unique<Object>(path, w, h);
  objs.push_back(std::move(ptr));
  nObjs++;
  return nObjs - 1;
}

void Scene::deleteObj(unsigned id) { objs.erase(objs.begin() + id); }
