#pragma once

#include "EngineState.h"

struct Color
{
	int r, g, b, a;
};

class RectangleRenderer
{
public:
	float width, height;
	Color color;

	GameObject* owner = nullptr;

	RectangleRenderer(float w, float h, Color col);
	
	void Draw(EngineState* engine);
	void SetColor(Color col);
};