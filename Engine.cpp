#include "Engine.h"
#include "SceneView.h"

#include <iostream>

void Engine::init() {
    // initialize window/renderer
}

void Engine::run() {
    // Selects every entity with TransformComponent
    auto view = SceneView<Components::Transform>(*this->scenes[currentScene]);

    // iterates through elements
    for (auto element : view) {
        auto component = this->scenes[currentScene]->get<Components::Transform>(element);
        std::cout << component->x << component->y << std::endl;

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

