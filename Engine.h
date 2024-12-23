#pragma once
#include <vector>

#include "Scene.h"
#include "SceneView.h"


class Engine {
private:
  std::vector<Scene*> scenes;
  int currentScene = 0;
public:
  Engine()= default;
  ~Engine()= default;
  void init();
  void run();
  void addScene(Scene* scene);
  void swapScene(int sceneID);
  void cleanup();

private:

};
