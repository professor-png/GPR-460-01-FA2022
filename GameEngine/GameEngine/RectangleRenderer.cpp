#include "RectangleRenderer.h"
#include "GameObject.h"

RectangleRenderer::RectangleRenderer(int w, int h, Color col)
{
	width = w;
	height = h;
	color = col;
	originalColor = col;
}

void RectangleRenderer::Draw(EngineState* engine)
{
	SDL_Rect rect = {(int)owner->GetTransform()->x, (int)owner->GetTransform()->y, width, height};
	
	SDL_SetRenderDrawColor(engine->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(engine->renderer, &rect);
}

void RectangleRenderer::SetColor(Color col)
{
	color = col;
}