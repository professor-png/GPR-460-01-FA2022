#include "PlayerController.h"

void PlayerController::Update(EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDLK_RIGHT])
    {
        owner->GetTransform()->x -= 1;
    }

    if (state[SDLK_LEFT])
    {
        owner->GetTransform()->x += 1;
    }

    if (state[SDLK_UP])
    {
        owner->GetTransform()->y -= 1;
    }

    if (state[SDLK_DOWN])
    {
        owner->GetTransform()->y += 1;
    }
}