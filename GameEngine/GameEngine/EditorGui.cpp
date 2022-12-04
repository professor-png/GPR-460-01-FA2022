#include "EditorGui.h"

EditorGui::EditorGui()
{
	imGuiContext = nullptr;
}
EditorGui::~EditorGui()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void EditorGui::InitGui(SDL_Window* window, SDL_Renderer* renderer)
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
}

void EditorGui::DrawGui()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	imGuiContext = ImGui::GetCurrentContext();

	//ImGui::SetCurrentContext(imGuiContext);
	ImGui::Begin("Settings", nullptr);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}