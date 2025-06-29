#pragma once

#include <Engine/Core/Window.h>
#include <Engine/Core/Input.h>
#include <Engine/Core/AssetManager.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Scene/Scene.h>

class Engine {

public:
    Engine();
    ~Engine();
    bool Create(const char* title, int w, int h);
    void Run();

private:
    Window window;
    Input input;

    Renderer renderer;
    Scene scene;

};