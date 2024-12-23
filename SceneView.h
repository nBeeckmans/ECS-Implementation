#pragma once
#include "Scene.h"

template<typename... ComponentTypes>
class SceneView {
private:
    Scene* pScene = nullptr;
    ComponentMask componentMask;
    bool all {false};
public:
    SceneView(Scene& scene) : pScene(&scene) {
        if (sizeof ... (ComponentTypes) == 0) {
            all = true;
        }
        else {
            int componentIndices[] = {0,Components::getID<ComponentTypes>()...};
            for (int i = 0; i < sizeof ... (ComponentTypes); i++) {
                componentMask.set(componentIndices[i]);
            }

        }
    };

    struct Iterator {
        Scene* pScene;
        EntityIndex index;
        ComponentMask componentMask;
        bool all {false};
        Iterator() = default;
        Iterator(Scene* pScene, EntityIndex id, ComponentMask mask, bool all)
        : pScene(pScene), index(id), componentMask(mask), all(all) {

        };
        EntityID operator*() const {
            return pScene->entities[index].getID();
        }

        bool operator==(const Iterator& other) const {
            return index == other.index || index == pScene->entities.size();
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index && index != pScene->entities.size();
        }

        bool validIndex() {
            return Entity::isValid(pScene->entities[index].getID()) &&
                (all|| componentMask == (componentMask & pScene->entities[index].getMask()));
        }

        Iterator& operator++() {
            do {
                ++index;
            } while (index != pScene->entities.size() && !validIndex());
            return *this;
        }
    };

    const Iterator& begin() const {
        int firstIndex = 0;
        while (firstIndex < pScene->entities.size() && (componentMask != (componentMask & pScene->entities[firstIndex].getMask()))
            || !Entity::isValid(pScene->entities[firstIndex].getID())) {
            firstIndex++;
        }
        return Iterator(pScene, firstIndex, componentMask, all);
    };

    const Iterator& end() const {
        return Iterator(pScene, pScene->entities.size(), componentMask, all);
    };

};
