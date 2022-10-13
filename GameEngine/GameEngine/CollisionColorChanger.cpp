#include "CollisionColorChanger.h"

#include "GameObject.h"
#include "RectangleRenderer.h"

CollisionColorChanger::CollisionColorChanger()
{

}

void CollisionColorChanger::Update(Color color)
{
	owner->GetRenderer()->color = color;
}

void CollisionColorChanger::Update(CollisionColorChanger* colorChanger, Color color)
{
	colorChanger->owner->GetRenderer()->color = color;
}