#include "PlayerController.h"
#include "GameObject.h"

PlayerController::PlayerController()
{

}

void PlayerController::Update(/*PlayerController player, */EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x + 1, owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x - 1, owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_UP])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x, owner->GetTransform()->position.y - 1);
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x, owner->GetTransform()->position.y + 1);
    }
}