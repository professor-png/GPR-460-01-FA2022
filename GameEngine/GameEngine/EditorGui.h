#pragma once

#include <iostream>
#include <ImGui/imgui.h>
#include <SDL2/SDL.h>
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_sdlrenderer.h>

class World;
class GameObject;

class EditorGui
{
private:
	void* selectedComp = nullptr;
	int selectedObjIndex = 0;
	std::string selectedCompName = "";

public:
	EditorGui();
	~EditorGui();
	GameObject* selectedObj = nullptr;

	void ShutDown();
	void InitGui(SDL_Window* window, SDL_Renderer* renderer);
	void DrawGui(World* world);
};