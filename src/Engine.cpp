#include <Engine/Engine.h>
#include <iostream>


Engine::Engine()
{
}

Engine::~Engine()
{
    AssetManager::ClearShaders();
}

bool Engine::Create(const char* title, int w, int h)
{
    if(!window.Init(title, w, h))
    {
        return false;
    }
    
    return true;
}

void Engine::Run()
{
    SDL_GL_SetSwapInterval(1); 
    while(!input.ShutDown())
    {
        SDL_Event event;
        while(window.PollEvent(event))
        {
            input.OnEvent(event);
        }
        renderer.Clear();
        app.GetSceneManager()->GetCurrentScene()->DrawQuads(renderer);
        
        window.Update();
    }
}

