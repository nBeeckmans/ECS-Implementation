#pragma once
#include <cstddef>

#include "Entity.h"

typedef char byte;

class ComponentPool {
private:
    byte* pPool {nullptr};
    std::size_t elementSize {0};
public:
    explicit ComponentPool(std::size_t elementSize) : elementSize(elementSize) {
        pPool = new byte[elementSize * MAX_ENTITIES];
    };

    ~ComponentPool() {
        delete[] pPool;
    };

    inline void* get(std::size_t index) {
        return this->pPool + index * elementSize;
    }
};
