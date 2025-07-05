#pragma once

#include <Engine/Engine.h>

class Application {
public:
    Application(){}

    bool Create(const char* title, int w, int h){return engine.Create(title, w, h);}

    void Run();

    Engine& GetEngine(){return engine;}

private:
    //std::shared_ptr<SceneManager> sceneManager;
    Engine engine;
};