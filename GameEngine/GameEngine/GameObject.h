#pragma once

#include "Transform.h"
#include "RectangleCollider.h"
#include "RectangleRenderer.h"
#include "PlayerController.h"
#include "CollisionColorChanger.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    RectangleRenderer* CreateRenderer(float width, float height, Color color);
    RectangleCollider* CreateCollider();
    PlayerController* CreatePlayerController();
    CollisionColorChanger* CreateColliderColorChanger();

    Transform* GetTransform();
    RectangleRenderer* GetRenderer();
    RectangleCollider* GetCollider();

    void Update(EngineState* engine);

protected:
    Transform transform;
    RectangleRenderer* renderer;
    RectangleCollider* collider;
    PlayerController* player;
    CollisionColorChanger* colorChanger;

};
