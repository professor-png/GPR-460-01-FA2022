#include "GameObject.h"

GameObject::GameObject(std::string objName)
{
    name = objName;
    transform = Transform();
    renderer = nullptr;
    collider = nullptr;
    player = nullptr;
    colorChanger = nullptr;
}

GameObject::GameObject(std::string objName, int x, int y)
{
    name = objName;
    transform = Transform(x, y);
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

RectangleRenderer* GameObject::CreateRenderer(float width, float height, Color color)
{
    renderer = new RectangleRenderer(width, height, color);
    renderer->owner = this;
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
    colorChanger->owner = this;
    return colorChanger;
}
