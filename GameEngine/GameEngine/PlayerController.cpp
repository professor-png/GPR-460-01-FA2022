#include "PlayerController.h"
#include "GameObject.h"
#include <iostream>

PlayerController::PlayerController()
{

}

void PlayerController::Update(EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        owner->GetTransform()->x += 1;
        std::cout << "right\n";
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        owner->GetTransform()->x -= 1;
        std::cout << "left\n";
    }

    if (state[SDL_SCANCODE_UP])
    {
        owner->GetTransform()->y -= 1;
        std::cout << "up\n";
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        owner->GetTransform()->y += 1;
        std::cout << "down\n";
    }
}