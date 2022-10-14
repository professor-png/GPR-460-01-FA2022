#include "EngineState.h"
#include "RectangleRenderer.h"
#include "GameObject.h"

RectangleRenderer::RectangleRenderer()
{
	width = 10;
	height = 10;
	color = Color();
	originalColor = Color();
}

RectangleRenderer::RectangleRenderer(int w, int h, Color col)
{
	width = w;
	height = h;
	color = col;
	originalColor = col;
}

RectangleRenderer::~RectangleRenderer()
{
	//ShutDown();
}

void RectangleRenderer::ShutDown()
{
	/*if (owner != nullptr)
		delete owner;*/

	owner = nullptr;
}

void RectangleRenderer::Draw(EngineState* engine)
{
	SDL_Rect rect = {owner->GetTransform()->position.x, owner->GetTransform()->position.y, width, height};
	
	SDL_SetRenderDrawColor(engine->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(engine->renderer, &rect);
}

void RectangleRenderer::Draw(RectangleRenderer* renderer, EngineState* engine)
{
	SDL_Rect rect = { renderer->owner->GetTransform()->position.x, renderer->owner->GetTransform()->position.y, renderer->width, renderer->height };

	SDL_SetRenderDrawColor(engine->renderer, renderer->color.r, renderer->color.g, renderer->color.b, renderer->color.a);
	SDL_RenderFillRect(engine->renderer, &rect);
}

void RectangleRenderer::SetColor(Color col)
{
	color = col;
}