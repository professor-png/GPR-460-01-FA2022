#pragma once
class GameObject;

class RectangleCollider
{
private:
	bool colliding = false;

public:
	RectangleCollider();
	~RectangleCollider();

	void ShutDown();
	bool GetColliding();
	void SetColliding(bool collider);

	bool CheckCollisions(RectangleCollider* other);
	GameObject* owner = nullptr;
};