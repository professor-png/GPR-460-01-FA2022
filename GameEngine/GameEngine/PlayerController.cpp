#include "EngineState.h"
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

void Update(PlayerController* player, EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        player->owner->GetTransform()->position = Vector2(player->owner->GetTransform()->position.x + 1, player->owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        player->owner->GetTransform()->position = Vector2(player->owner->GetTransform()->position.x - 1, player->owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_UP])
    {
        player->owner->GetTransform()->position = Vector2(player->owner->GetTransform()->position.x, player->owner->GetTransform()->position.y - 1);
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        player->owner->GetTransform()->position = Vector2(player->owner->GetTransform()->position.x, player->owner->GetTransform()->position.y + 1);
    }
}