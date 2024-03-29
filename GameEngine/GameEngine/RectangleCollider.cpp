#include "RectangleCollider.h"
#include "GameObject.h"

RectangleCollider::RectangleCollider()
{

}

RectangleCollider::~RectangleCollider()
{
    //ShutDown();
}

void RectangleCollider::ShutDown()
{
    /*if (owner != nullptr)
        delete owner;*/

    owner = nullptr;
}

bool RectangleCollider::GetColliding()
{ 
    return colliding;
}

void RectangleCollider::SetColliding(bool collider)
{
    colliding = collider;
}

bool RectangleCollider::CheckCollisions(RectangleCollider* other)
{
    if (other == nullptr || this == nullptr)
        return false;

    return (owner->GetTransform()->position.x < other->owner->GetTransform()->position.x + other->owner->GetRenderer()->width &&
        owner->GetTransform()->position.x + owner->GetRenderer()->width > other->owner->GetTransform()->position.x &&
        owner->GetTransform()->position.y < other->owner->GetTransform()->position.y + other->owner->GetRenderer()->height &&
        owner->GetRenderer()->height + owner->GetTransform()->position.y > other->owner->GetTransform()->position.y);
}
