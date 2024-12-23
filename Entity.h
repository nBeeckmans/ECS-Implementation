#pragma once
#include <array>
#include <bitset>

#include "Components.h"

typedef unsigned int EntityIndex;
typedef std::bitset<Components::MAX_COMPONENTS> ComponentMask;
typedef unsigned int EntityVersion;
typedef long long unsigned int EntityID;

static EntityID nextEntityID = 0;

class Entity {
private:
  EntityID id;
  ComponentMask flags;
public:
  Entity(){ this->id = nextEntityID++; }
  Entity(EntityID id, ComponentMask flags){}
  EntityID getID() { return id; }
  void setID(EntityID id) { this->id = id; }
  void setComponent(int componentID) { this->flags.set(componentID); }
  bool hasComponent(int componentID) { return this->flags.test(componentID); }
  void removeComponent(int componentID) { this->flags.reset(componentID); }
  ComponentMask getMask() { return this->flags; }
  void reset() { this->flags.reset(); }

  static inline EntityID createEntityID(EntityIndex index, EntityVersion version) {
    return (static_cast<EntityID>(index) << 32) | static_cast<EntityID>(version);
  }

  static inline EntityIndex getEntityIndex(EntityID id) {
    return id >> 32;
  }

  static inline EntityVersion getEntityVersion(EntityID id) {
    return id & 0xFFFFFFFF;
  }

  static inline bool isValid(EntityID id) {
    return (id >> 32) != EntityIndex(-1);
  }
private:
};

#define INVALID_ENTITY_INDEX Entity::createEntityIndex(EntityIndex(-1), 0)
