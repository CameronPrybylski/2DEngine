#pragma once

#include <SDL.h>
#include <glad/glad.h>

class Window {

public:
    Window();
    ~Window();

    bool Init(const char* title, int width, int height);
    void Update();
    bool ShutDown();
    bool PollEvent(SDL_Event& event);

private:
    SDL_Window* window;
    SDL_GLContext glContext;

    bool shouldClose = false;

};