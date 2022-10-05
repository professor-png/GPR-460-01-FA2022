#include "RectangleRenderer.h"
#include "GameObject.h"

RectangleRenderer::RectangleRenderer(float w, float h, Color col)
{
	width = w;
	height = h;
	color.r = col.r;
	color.g = col.g;
	color.b = col.b;
	color.a = col.a;
}

void RectangleRenderer::Draw(EngineState* engine)
{
	SDL_Rect rect = {owner->GetTransform()->x, owner->GetTransform()->y, width, height};
	
	SDL_SetRenderDrawColor(engine->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(engine->renderer, &rect);
}

void RectangleRenderer::SetColor(Color col)
{
	color = col;
}