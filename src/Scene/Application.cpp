#include <Engine/Scene/Application.h>
/*
SceneManager* Application::GetSceneManager()
{
    return sceneManager.get();
}

*/
bool Application::Create(const char* title, int w, int h)
{
    screenWidth = (float)w;
    screenHeigt = (float)h;
    return engine.Create(title, w, h);
}

void Application::Run()
{
    engine.Run();
    /*
    SDL_GL_SetSwapInterval(1); 
    while(!engine.getInput().ShutDown())
    {
        SDL_Event event;
        while(engine.getWindow().PollEvent(event))
        {
            engine.getInput().OnEvent(event);
        }
        engine.getRenderer().Clear();
        engine.GetSceneManager()->GetCurrentScene()->DrawQuads(engine.getRenderer());
        
        engine.getWindow().Update();
    }
        */
}

void Application::AddScene(std::string sceneName, std::shared_ptr<Scene> scene)
{
    engine.GetSceneManager()->AddScene(sceneName, scene);
}

void Application::SetScene(std::string sceneName)
{
    engine.GetSceneManager()->SwitchTo(sceneName);
}