#include "GameObject.h"

GameObject::GameObject()
{
    transform = Transform();
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

}

RectangleRenderer* GameObject::CreateRenderer(float width, float height, int r, int g, int b, int a)
{
    renderer = new RectangleRenderer(width, height, r, g, b, a);
    return renderer;
}

RectangleCollider* GameObject::CreateCollider()
{
    collider->owner = this;
    return collider;
}

PlayerController* GameObject::CreatePlayerController()
{
    player->owner = this;
    return player;
}

CollisionColorChanger* GameObject::CreateColliderColorChanger()
{

    return nullptr;
}
