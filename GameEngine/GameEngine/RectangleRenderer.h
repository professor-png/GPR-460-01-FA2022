#pragma once

#include "EngineState.h"

struct Color
{
	int r, g, b, a;

	Color(int red, int green, int blue, int alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
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