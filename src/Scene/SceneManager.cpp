#include <Engine/Scene/SceneManager.h>

void SceneManager::AddScene(std::string sceneName, std::shared_ptr<Scene> scene)
{
    scenes[sceneName] = scene;
}

void SceneManager::SwitchTo(std::string sceneName)
{
    if(scenes.find(sceneName) != scenes.end())
    {
        currentScene = scenes[sceneName].get();
    }
}

Scene* SceneManager::GetCurrentScene()
{
    return currentScene;
}