#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const GameObject& gameObject)
{
    name = gameObject.name;
    transform = gameObject.transform;
    renderer = gameObject.renderer;
    collider = gameObject.collider;
    player = gameObject.player;
    colorChanger = gameObject.colorChanger;
}

GameObject::GameObject(std::string objName)
{
    name = objName;
    transform = Transform();
    renderer = nullptr;
    collider = nullptr;
    player = nullptr;
    colorChanger = nullptr;
}

GameObject::GameObject(std::string objName, Transform position)
{
    name = objName;
    transform = position;
    renderer = nullptr;
    collider = nullptr;
    player = nullptr;
    colorChanger = nullptr;
}

GameObject::~GameObject()
{
    if (renderer != nullptr)
    {
        delete renderer;
        renderer = nullptr;
    }

    if (collider != nullptr)
    {
        delete collider;
        collider = nullptr;
    }

    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }

    if (colorChanger != nullptr)
    {
        delete colorChanger;
        colorChanger = nullptr;
    }
}

Transform* GameObject::GetTransform()
{
    return &transform;
}

RectangleRenderer* GameObject::GetRenderer()
{
    return renderer;
}

RectangleCollider* GameObject::GetCollider()
{
    return collider;
}

void GameObject::Update(EngineState* engine)
{
    if (player != nullptr)
        player->Update(engine);

    if (collider != nullptr)
    {
        bool collision = false;
        for (auto obj : engine->gameObjects)
        {
            if (obj->name != name && obj->collider != nullptr)
            {
                collision = collider->CheckCollisions(obj->GetCollider());

                if (collision)
                    colorChanger->Update(Color(0, 0, 200, 255));
                else
                    colorChanger->Update(renderer->originalColor);
            }
        }
    }

    if (renderer != nullptr)
        renderer->Draw(engine);
}

RectangleRenderer* GameObject::CreateRenderer(RectangleRenderer* rectRenderer)
{
    if (renderer == nullptr)
    {
        renderer = rectRenderer;
        renderer->owner = this;
    }
    return renderer;
}

RectangleCollider* GameObject::CreateCollider(RectangleCollider* rectCollider)
{
    if (collider == nullptr)
    {
        collider = rectCollider;
        collider->owner = this;
    }
    return collider;
}

PlayerController* GameObject::CreatePlayerController(PlayerController* playerController)
{
    if (player == nullptr)
    {
        player = playerController;
        player->owner = this;
    }
    return player;
}

CollisionColorChanger* GameObject::CreateColliderColorChanger(CollisionColorChanger* colChanger)
{
    if (colorChanger == nullptr)
    {
        colorChanger = colChanger;
        colorChanger->owner = this;
    }
    return colorChanger;
}
