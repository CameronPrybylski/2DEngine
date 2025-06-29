#include <Engine/Engine.h>
#include <iostream>


Engine::Engine()
{

}

Engine::~Engine()
{

}

bool Engine::Create(const char* title, int w, int h)
{
    if(!window.Init(title, w, h))
    {
        return false;
    }
    auto quadMesh = std::make_shared<QuadMesh>();
    std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
    object->mesh = quadMesh;
    object->shaderName = "objectShader";
    scene.AddObject(object);
    AssetManager::LoadShader("objectShader", "../shaders/basic.vert", "../shaders/basic.frag");
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    return true;
}

void Engine::Run()
{
    while(!input.ShutDown())
    {
        SDL_Event event;
        while(window.PollEvent(event))
        {
            input.OnEvent(event);
        }
        scene.Draw(renderer);
        scene.Clear(renderer);
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark gray background
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.Update();
    }
}

