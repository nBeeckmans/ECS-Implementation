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

    auto view = SceneView<Components::Transform, Components::BoundingBox>(mainScene);

    Engine engine;
    engine.init();
    engine.addScene(&mainScene);
    engine.run();
    engine.cleanup();

    return 0;
}
