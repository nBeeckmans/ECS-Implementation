#pragma once
#include <cassert>

namespace Components {
  constexpr int MAX_COMPONENTS = 32;
  extern int componentCount;

  template<class _>
  int getID() {
    static int id = componentCount++;
    assert(id < MAX_COMPONENTS);
    return id;
  }

  struct Transform {
    int x,y;
  };

  struct BoundingBox {
    int x,y,w,h;
  };
}