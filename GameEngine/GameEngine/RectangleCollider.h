#pragma once
class GameObject;

class RectangleCollider
{
public:
	bool CheckCollisions(RectangleCollider* other);
	GameObject* owner = nullptr;
};