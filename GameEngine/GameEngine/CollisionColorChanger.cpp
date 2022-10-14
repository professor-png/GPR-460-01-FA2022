#include "CollisionColorChanger.h"
#include "GameObject.h"
#include "RectangleRenderer.h"

CollisionColorChanger::CollisionColorChanger()
{

}

CollisionColorChanger::~CollisionColorChanger()
{
	ShutDown();
}

void CollisionColorChanger::ShutDown()
{
	if (owner != nullptr)
		delete owner;

	owner = nullptr;
}

void CollisionColorChanger::Update(Color color)
{
	owner->GetRenderer()->color = color;
}

void CollisionColorChanger::Update(CollisionColorChanger* colorChanger, Color color)
{
	colorChanger->owner->GetRenderer()->color = color;
}