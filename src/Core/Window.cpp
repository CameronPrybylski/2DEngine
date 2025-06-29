#include <Engine/Core/Window.h>
#include <iostream>

Window::Window()
{
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::Init(const char* title, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(!window)
        {
            std::cerr << "Error creating window" << SDL_GetError() << std::endl;
            return false;
        }

        glContext = SDL_GL_CreateContext(window);

        if (!glContext) {
            std::cerr << "Failed to create GL context: " << SDL_GetError() << std::endl;
            return false;
        }

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        std::cout << "Running OpenGL version: " << glGetString(GL_VERSION) << std::endl;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        return true;
    }
    else
    {
        std::cerr << "SDL Failed to init Everything" << std::endl;
        return false;
    }
}

void Window::Update()
{
    SDL_GL_SwapWindow(window);
}

bool Window::ShutDown()
{
    return shouldClose;
}

bool Window::PollEvent(SDL_Event& event)
{
    return SDL_PollEvent(&event);  
}