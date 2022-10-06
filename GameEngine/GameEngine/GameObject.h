#pragma once

#include "Transform.h"
#include "RectangleCollider.h"
#include "RectangleRenderer.h"
#include "PlayerController.h"
#include "CollisionColorChanger.h"

class GameObject
{
public:
    GameObject(std::string objName);
    GameObject(std::string objName, int x, int y);
    ~GameObject();

    RectangleRenderer* CreateRenderer(int width, int height, Color color);
    RectangleCollider* CreateCollider();
    PlayerController* CreatePlayerController();
    CollisionColorChanger* CreateColliderColorChanger();

    Transform* GetTransform();
    RectangleRenderer* GetRenderer();
    RectangleCollider* GetCollider();

    void Update(EngineState* engine);

protected:
    std::string name;
    Transform transform;
    RectangleRenderer* renderer;
    RectangleCollider* collider;
    PlayerController* player;
    CollisionColorChanger* colorChanger;

};
