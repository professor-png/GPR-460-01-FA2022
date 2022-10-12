#include "Transform.h"

Transform::Transform()
{
	position.x = 0;
	position.y = 0;
}

Transform::Transform(Vector2 pos)
{
	position = pos;
}