#include "RectangleCollider.h"
#include "GameObject.h"

bool RectangleCollider::CheckCollisions(RectangleCollider* other)
{
    return (owner->GetTransform()->x < other->owner->GetTransform()->x + other->owner->GetRenderer()->width &&
        owner->GetTransform()->x + owner->GetRenderer()->width > other->owner->GetTransform()->x &&
        owner->GetTransform()->y < other->owner->GetTransform()->y + other->owner->GetRenderer()->height &&
        owner->GetRenderer()->height + owner->GetTransform()->y > other->owner->GetTransform()->y);
}