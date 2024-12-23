#pragma once
#include <bitset>

#include "Components.h"

typedef unsigned int EntityIndex;
typedef std::bitset<Components::MAX_COMPONENTS> ComponentMask;
typedef unsigned int EntityVersion;
typedef long long unsigned int EntityID;

static EntityID nextEntityID = 0;
constexpr int MAX_ENTITIES = 32;

class Entity {
private:
  EntityID id;
  ComponentMask flags;
public:
  Entity(){ this->id = nextEntityID++; }
  Entity(const EntityID id, const ComponentMask flags)
  : id(id), flags(flags) {}

  [[nodiscard]] EntityID getID() const { return id; }
  void setID(const EntityID id) { this->id = id; }
  void setComponent(int componentID) { this->flags.set(componentID); }
  [[nodiscard]] bool hasComponent(int componentID) const { return this->flags.test(componentID); }
  void removeComponent(int componentID) { this->flags.reset(componentID); }
  [[nodiscard]] ComponentMask getMask() const { return this->flags; }
  void reset() { this->flags.reset(); }

  static inline EntityID createEntityID(EntityIndex index, EntityVersion version) {
    return (static_cast<EntityID>(index) << 32) | static_cast<EntityID>(version);
  }

  static inline EntityIndex getEntityIndex(const EntityID id) {
    return id >> 32;
  }

  static inline EntityVersion getEntityVersion(const EntityID id) {
    return id & 0xFFFFFFFF;
  }

  static inline bool isValid(const EntityID id) {
    return (id >> 32) != static_cast<EntityIndex>(-1);
  }
private:
};

#define INVALID_ENTITY_INDEX Entity::createEntityIndex(EntityIndex(-1), 0)
