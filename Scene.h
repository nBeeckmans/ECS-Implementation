#pragma once
#include <optional>
#include <vector>

#include "ComponentPool.h"
#include "Entity.h"


class Scene {
    std::vector<Entity> entities;
    std::vector<EntityIndex> freeEntities;
    std::vector<ComponentPool*> componentPools;
public:
    EntityID createEntity() {
        if (!freeEntities.empty()) {
            EntityIndex newIndex = freeEntities.back();
            freeEntities.pop_back();
            EntityID newEntity =
                Entity::createEntityID(
                    newIndex,
                    Entity::getEntityVersion(entities[newIndex].getID())
                    );
            entities[newEntity].setID(newIndex);
            return entities[newEntity].getID();
        }
        entities.emplace_back(
            Entity::createEntityID(Entity::getEntityIndex(entities.size()),0),
        ComponentMask()
        );
        return this->entities.back().getID();
    } ;

    template<typename T>
    T* assign(EntityID entityID) {
        int componentID = Components::getID<T>();

        if (componentPools.size() <= componentID) {
            componentPools.resize(componentID + 1, nullptr);
        }

        if (componentPools[componentID] == nullptr) {
            componentPools[componentID] = new ComponentPool(sizeof(T));
        }

        T* component = new (componentPools[componentID]->get(componentID)) T();
        entities[entityID].setComponent(componentID);
        return component;
    }

    template<typename T>
    std::optional<T*> get(EntityID entityId) {
        int componentID = Components::getID<T>();
        if (!entities[entityId].hasComponent(componentID)) {
            return std::nullopt;
        }

        T* pComponent = static_cast<T*>(componentPools[componentID]->get(componentID));
        return pComponent;
    }

    template <typename T>
    void remove(EntityID entityID) {
        if (entities[Entity::getEntityIndex(entityID)].getID() != entityID) {
            return;
        }

        int componentID = Components::getID<T>();
        entities[Entity::getEntityIndex(entityID)].removeComponent(componentID);
    }

    void DestroyEntity(EntityID entityID) {
        EntityID newID =
            Entity::createEntityID(
                Entity::getEntityIndex(-1),
                    Entity::getEntityVersion(entityID)+1
                    );
        entities[Entity::getEntityIndex(entityID)].setID(newID);
        entities[Entity::getEntityIndex(entityID)].reset();

        freeEntities.push_back(Entity::getEntityIndex(entityID));
    }

    template<typename... ComponentTypes>
    friend class SceneView;
};
