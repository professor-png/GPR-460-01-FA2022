#include "RectangleCollider.h"
#include "GameObject.h"

RectangleCollider::RectangleCollider()
{

}

bool RectangleCollider::CheckCollisions(RectangleCollider* other)
{
    return (owner->GetTransform()->position.x < other->owner->GetTransform()->position.x + other->owner->GetRenderer()->width &&
        owner->GetTransform()->position.x + owner->GetRenderer()->width > other->owner->GetTransform()->position.x &&
        owner->GetTransform()->position.y < other->owner->GetTransform()->position.y + other->owner->GetRenderer()->height &&
        owner->GetRenderer()->height + owner->GetTransform()->position.y > other->owner->GetTransform()->position.y);
}