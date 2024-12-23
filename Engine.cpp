#include "Engine.h"

#include <iostream>

void Engine::init() {

}

void Engine::run() {
    auto view = SceneView<Components::Transform>(*this->scenes[currentScene]);
    auto test = view.begin();

    for (auto element : view) {
        auto component = this->scenes[currentScene]->get<Components::Transform>(element);
        if (component.has_value()) {
            std::cout << component.value()->x << component.value()->y << std::endl;
        }
    }
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

