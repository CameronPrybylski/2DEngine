#pragma once

#include <Engine/Scene/SceneManager.h>

class Application {
public:
    Application(){sceneManager = std::make_shared<SceneManager>();}
    SceneManager* GetSceneManager();

private:
    std::shared_ptr<SceneManager> sceneManager;
};