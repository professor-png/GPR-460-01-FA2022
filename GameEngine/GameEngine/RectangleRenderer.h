#pragma once

//#include "EngineState.h"
struct EngineState;

struct Color
{
	int r, g, b, a;

	Color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

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
	int width, height;
	Color originalColor, color;

	GameObject* owner = nullptr;
	RectangleRenderer();
	RectangleRenderer(int w, int h, Color col);
	~RectangleRenderer();
	
	void ShutDown();
	void Draw(EngineState* engine);
	static void Draw(RectangleRenderer* renderer, EngineState* engine);
	void SetColor(Color col);
};