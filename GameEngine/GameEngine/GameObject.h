#pragma once

#include "Transform.h"
#include "RectangleCollider.h"
#include "RectangleRenderer.h"
#include "PlayerController.h"
#include "CollisionColorChanger.h"

#include <iostream>

class GameObject
{
private:
    static int numUnNamedObjects;
public:
    GameObject();
    GameObject(const GameObject& gameObject);
    GameObject(std::string objName);
    GameObject(std::string objName, Transform position);
    ~GameObject();

    void ShutDown();

    RectangleRenderer* CreateRenderer(RectangleRenderer* rectRenderer/*int width, int height, Color color*/);
    RectangleCollider* CreateCollider(RectangleCollider* rectCollider);
    PlayerController* CreatePlayerController(PlayerController* playerController);
    CollisionColorChanger* CreateColliderColorChanger(CollisionColorChanger* colChanger);

    void SetName(std::string newName) { name = newName; }

    std::string GetName();
    Transform* GetTransform();
    RectangleRenderer* GetRenderer();
    RectangleCollider* GetCollider();
    PlayerController* GetPlayerController();
    CollisionColorChanger* GetCollisionColorChanger();
    void SetPosition(Vector2 vec);

    void Update(EngineState* engine);

    void SetRenderer(RectangleRenderer* rend) { renderer = rend; }
    void SetCollider(RectangleCollider* col) { collider = col; }
    void SetPlayerController(PlayerController* control) { player = control; }
    void SetColorChanger(CollisionColorChanger* changer) { colorChanger = changer; }

    void DeleteRectangleRenderer();
    void DeleteRectangleCollider();
    void DeletePlayerController();
    void DeleteCollisionColorChanger();

protected:
    std::string name = "";
    Transform transform;
    RectangleRenderer* renderer;
    RectangleCollider* collider;
    PlayerController* player;
    CollisionColorChanger* colorChanger;

};
