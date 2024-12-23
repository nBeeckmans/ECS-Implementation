#include <iostream>

#include "Engine.h"
#include "Components.h"

int Components::componentCount = 0;

void setupScene();

void setupScene(Scene& scene) {
    auto entity = scene.createEntity();
    scene.assign<Components::Transform>(entity);
}

int main() {
    Scene mainScene;
    setupScene(mainScene);
    auto entity = mainScene.createEntity();
    auto component = mainScene.assign<Components::Transform>(entity);
    component->x = 10;
    component->y = 440;

    auto entity2 = mainScene.createEntity();
    auto component2 = mainScene.assign<Components::BoundingBox>(entity2);
    component2->x = 50;
    component2->y = 50;

    Engine engine;
    engine.init();
    engine.addScene(&mainScene);
    engine.run();
    engine.cleanup();

    return 0;
}
