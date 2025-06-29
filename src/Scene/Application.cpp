#include <Engine/Scene/Application.h>

SceneManager* Application::GetSceneManager()
{
    return sceneManager.get();
}