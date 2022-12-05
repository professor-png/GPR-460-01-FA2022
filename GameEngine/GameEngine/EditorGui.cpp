#include "EditorGui.h"
#include "World.h"

EditorGui::EditorGui()
{
	
}
EditorGui::~EditorGui()
{
	ShutDown();
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void EditorGui::ShutDown()
{
	/*ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();*/

	selectedObj = nullptr;
	selectedObjIndex = 0;
}

void EditorGui::InitGui(SDL_Window* window, SDL_Renderer* renderer)
{
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
}

void EditorGui::DrawGui(World* world)
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//ImGui::SetCurrentContext(imGuiContext);
	ImGui::Begin("Settings", nullptr);

	if (ImGui::BeginCombo("##GameObjects", "GameObjects"))
	{
		for (int i = 0; i < world->numActiveObjects; i++)
		{
			bool selected = (world->gameObjects[selectedObjIndex].GetName() == world->gameObjects[i].GetName());

			if (ImGui::Selectable(world->gameObjects[i].GetName().c_str(), selected))
			{
				selectedObj = &world->gameObjects[i];
				selectedObjIndex = i;
			}

			if (selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::Text("Selected Object:");

	if (selectedObj != nullptr)
	{
		ImGui::Text(selectedObj->GetName().c_str());
		if (ImGui::BeginCombo("##Components", "Components"))
		{
			bool selected = false;
			int i;

			//player controller
			if (selectedObj->GetPlayerController() != nullptr)
			{
				for (i = 0; i < world->numActivePlayerControllers; i++)
				{
					selected = (selectedComp == &world->playerControllers[i]);

					if (ImGui::Selectable("Player Controller", selected) && selectedObj->GetName() == world->playerControllers[i].owner->GetName())
					{
						selectedComp = &world->playerControllers[i];
						selectedCompName = "Player Controller";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
				}
			}
			
			//renderers
			if (selectedObj->GetRenderer() != nullptr)
			{
				for (i = 0; i < world->numActiveRectangleRenderers; i++)
				{
					selected = (selectedComp == &world->rectangleRenderers[i]);

					if (ImGui::Selectable("Renderer", selected) && selectedObj->GetName() == world->rectangleRenderers[i].owner->GetName())
					{
						selectedComp = &world->rectangleRenderers[i];
						selectedCompName = "Renderer";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
				}
			}

			//colliders
			if (selectedObj->GetCollider() != nullptr)
			{
				for (i = 0; i < world->numActiveRectangleColliders; i++)
				{
					selected = (selectedComp == &world->rectangleColliders[i]);

					if (ImGui::Selectable("Collider", selected) && selectedObj->GetName() == world->rectangleColliders[i].owner->GetName())
					{
						selectedComp = &world->rectangleColliders[i];
						selectedCompName = "Collider";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
				}
			}

			//color changers
			if (selectedObj->GetCollisionColorChanger() != nullptr)
			{
				for (i = 0; i < world->numActiveColorChangers; i++)
				{
					selected = (selectedComp == &world->collisionColorChangers[i]);

					if (ImGui::Selectable("Color Changer", selected) && selectedObj->GetName() == world->collisionColorChangers[i].owner->GetName())
					{
						selectedComp = &world->collisionColorChangers[i];
						selectedCompName = "Color Changer";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		ImGui::Text("Component");
		ImGui::Text(selectedCompName.c_str());
	}
	else
	{
		ImGui::Text("");
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}