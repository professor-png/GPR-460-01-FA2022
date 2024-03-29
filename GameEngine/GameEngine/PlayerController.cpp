#include "EngineState.h"
#include "PlayerController.h"
#include "GameObject.h"

PlayerController::PlayerController()
{

}

PlayerController::~PlayerController()
{
    //ShutDown();
}

void PlayerController::ShutDown()
{
    /*if (owner != nullptr)
        delete owner;*/

    owner = nullptr;
}

void PlayerController::Update(EngineState* engine)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x + speed, owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x - speed, owner->GetTransform()->position.y);
    }

    if (state[SDL_SCANCODE_UP])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x, owner->GetTransform()->position.y - speed);
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        owner->GetTransform()->position = Vector2(owner->GetTransform()->position.x, owner->GetTransform()->position.y + speed);
    }
}

void PlayerController::Update(PlayerController* player, EngineState* engine)
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