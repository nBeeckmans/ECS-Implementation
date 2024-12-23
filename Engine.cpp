#include "Engine.h"

void Engine::init() {

}

void Engine::run() {

}

void Engine::addScene(Scene *scene) {
    this->scenes.push_back(scene);
}

void Engine::swapScene(int sceneID) {
    assert(scenes.size() > sceneID && sceneID > 0);
    this->currentScene = sceneID;
}

void Engine::cleanup() {

}

