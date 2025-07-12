#pragma once

#include <Engine/Engine.h>

class Application {
public:
    Application(){}

    bool Create(const char* title, int w, int h){return engine.Create(title, w, h);}

    void Run();

    Engine& GetEngine(){return engine;}

    void AddScene(std::string sceneName, std::shared_ptr<Scene> scene);

private:
    //std::shared_ptr<SceneManager> sceneManager;
    Engine engine;
};