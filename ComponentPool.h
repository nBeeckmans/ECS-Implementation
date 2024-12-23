#pragma once
#include <cstddef>

typedef char byte;

class ComponentPool {
private:
    byte* pPool = nullptr;
    std::size_t elementSize = 0;
public:
    explicit ComponentPool(std::size_t elementSize) : elementSize(elementSize) {
        pPool = new byte[elementSize];
    };

    ~ComponentPool() {
        delete[] pPool;
    };

    inline void* get(std::size_t index) {
        return this->pPool + index * elementSize;
    }
private:

};
