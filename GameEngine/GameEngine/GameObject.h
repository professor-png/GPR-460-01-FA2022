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

    RectangleRenderer* CreateRenderer(float width, float height, int r, int g, int b, int a);
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
