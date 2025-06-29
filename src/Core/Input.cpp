#include <Engine/Core/Input.h>

void Input::OnEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        keysDown.insert(event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        keysDown.erase(event.key.keysym.scancode);
        break;
    case SDL_QUIT:
        shutDown = true;
        break;
    default:
        break;
    }
}

bool Input::IsKeyDown(SDL_Scancode scanCode)
{
    return keysDown.find(scanCode) != keysDown.end();
}

bool Input::ShutDown()
{
    return shutDown;
}