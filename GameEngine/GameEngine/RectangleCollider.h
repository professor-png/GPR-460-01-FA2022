#pragma once
class GameObject;

class RectangleCollider
{
public:
	RectangleCollider();

	bool CheckCollisions(RectangleCollider* other);
	GameObject* owner = nullptr;
};