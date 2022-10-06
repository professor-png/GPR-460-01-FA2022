#include "RectangleCollider.h"
#include "GameObject.h"

RectangleCollider::RectangleCollider()
{

}

bool RectangleCollider::CheckCollisions(RectangleCollider* other)
{
    //if (other->owner->GetCollider() != nullptr)
        return (owner->GetTransform()->x < other->owner->GetTransform()->x + other->owner->GetRenderer()->width &&
            owner->GetTransform()->x + owner->GetRenderer()->width > other->owner->GetTransform()->x &&
            owner->GetTransform()->y < other->owner->GetTransform()->y + other->owner->GetRenderer()->height &&
            owner->GetRenderer()->height + owner->GetTransform()->y > other->owner->GetTransform()->y);
    //else
    //    return false;
}