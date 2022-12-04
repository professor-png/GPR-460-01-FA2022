#pragma once

#include <ImGui/imgui.h>
#include <SDL2/SDL.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_sdlrenderer.h>

class EditorGui
{
private:
	ImGuiContext* imGuiContext;

public:
	EditorGui();
	~EditorGui();

	void InitGui(SDL_Window* window, SDL_Renderer* renderer);
	void DrawGui();
};