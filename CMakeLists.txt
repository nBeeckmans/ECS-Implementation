CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 23)
PROJECT(ECS-IMPLEMENTATION)

ADD_EXECUTABLE(example Main.cpp
        Components.h
        Engine.cpp
        Engine.h
        Entity.h
        Scene.h
        ComponentPool.h
)