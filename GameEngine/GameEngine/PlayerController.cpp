#include "PlayerController.h"
#include "GameObject.h"

PlayerController::PlayerController()
{

}

void PlayerController::Update(EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        owner->GetTransform()->x += 1;
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        owner->GetTransform()->x -= 1;
    }

    if (state[SDL_SCANCODE_UP])
    {
        owner->GetTransform()->y -= 1;
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        owner->GetTransform()->y += 1;
    }
}