#pragma once

#include <Engine/Core/Window.h>
#include <Engine/Core/Input.h>
#include <Engine/Core/AssetManager.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Scene/Application.h>

class Engine {

public:
    Engine();
    ~Engine();
    bool Create(const char* title, int w, int h);
    void SetApp(Application app){this->app = app;}
    void Run();

private:
    Window window;
    Input input;

    Renderer renderer;
    //Scene& scene;
    //std::unique_ptr<SceneManager> sceneManager;
    Application app;

};