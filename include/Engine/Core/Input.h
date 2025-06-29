#include <SDL.h>
#include <unordered_set>

class Input {

public:

    void OnEvent(const SDL_Event& event);
    bool IsKeyDown(SDL_Scancode scanCode);
    bool ShutDown();

private:
    std::unordered_set<SDL_Scancode> keysDown;
    bool shutDown = false;


};