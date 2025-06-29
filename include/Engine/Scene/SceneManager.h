#pragma once

#include<Engine/Scene/Scene.h>

class SceneManager{
public:
    void AddScene(std::string sceneName, std::shared_ptr<Scene> scene);
    Scene* GetCurrentScene();
    void SwitchTo(std::string sceneName);

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    Scene* currentScene;
};