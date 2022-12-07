#include "EditorGui.h"
#include "World.h"
#include <sstream>
std::string ConvertIntToString(int intValue)
{
	std::stringstream stringValue;
	stringValue << intValue;
	return stringValue.str();
}int ConvertStringToInt(std::string stringValue)
{
	int intValue;
	std::stringstream str;
	str << stringValue;
	str >> intValue;
	return intValue;
}
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
		ImGui::InputInt("X", &selectedObj->GetTransform()->position.x);
		ImGui::InputInt("Y", &selectedObj->GetTransform()->position.y);

		if (ImGui::BeginCombo("##Components", "Components"))
		{
			bool selected = false;
			int i;

			//player controller
			if (selectedObj->GetPlayerController() != nullptr)
			{
					selected = (selectedComp == selectedObj->GetPlayerController());

					if (ImGui::Selectable("Player Controller", selected) && selectedObj->GetName() == selectedObj->GetPlayerController()->owner->GetName())
					{
						selectedComp = selectedObj->GetPlayerController();
						selectedCompName = "Player Controller";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
			}
			else
			{
				if (ImGui::Selectable("Player Controller (+)", selected))
				{
					world->AddPlayerController(selectedObjIndex, PlayerController());
					selectedComp = selectedObj->GetPlayerController();
					selectedCompName = "PlayerConotrller";
				}
				if (selected)
					ImGui::SetItemDefaultFocus();
			}
			
			//renderers
			if (selectedObj->GetRenderer() != nullptr)
			{
					selected = (selectedComp == selectedObj->GetRenderer());

					if (ImGui::Selectable("Renderer", selected) && selectedObj->GetName() == selectedObj->GetRenderer()->owner->GetName())
					{
						selectedComp = selectedObj->GetRenderer();
						selectedCompName = "Renderer";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
			}
			else
			{
				if (ImGui::Selectable("Renderer (+)", selected))
				{
					world->AddRectangleRenderer(selectedObjIndex, RectangleRenderer());
					selectedComp = selectedObj->GetRenderer();
					selectedCompName = "Renderer";
				}
				if (selected)
					ImGui::SetItemDefaultFocus();
			}

			//colliders
			if (selectedObj->GetCollider() != nullptr)
			{
					selected = (selectedComp == selectedObj->GetCollider());

					if (ImGui::Selectable("Collider", selected) && selectedObj->GetName() == selectedObj->GetCollider()->owner->GetName())
					{
						selectedComp = selectedObj->GetCollider();
						selectedCompName = "Collider";
					}

					if (selected)
						ImGui::SetItemDefaultFocus();
			}
			else
			{
				if (ImGui::Selectable("Collider (+)", selected))
				{
					world->AddRectangleCollider(selectedObjIndex, RectangleCollider());
					selectedComp = selectedObj->GetCollider();
					selectedCompName = "Collider";
				}
				if (selected)
					ImGui::SetItemDefaultFocus();
			}

			//color changers
			if (selectedObj->GetCollisionColorChanger() != nullptr)
			{
				selected = (selectedComp == selectedObj->GetCollisionColorChanger());

				if (ImGui::Selectable("Color Changer", selected) && selectedObj->GetName() == selectedObj->GetCollisionColorChanger()->owner->GetName())
				{
					selectedComp = selectedObj->GetCollisionColorChanger();
					selectedCompName = "Color Changer";
				}

				if (selected)
					ImGui::SetItemDefaultFocus();
			}
			else
			{
				if (ImGui::Selectable("Color Changer (+)", selected))
				{
					world->AddCollisionColorChanger(selectedObjIndex, CollisionColorChanger());
					selectedComp = selectedObj->GetCollisionColorChanger();
					selectedCompName = "Color Changer";
				}
				if (selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}
		ImGui::Text("Component");
		ImGui::Text(selectedCompName.c_str());
		if (selectedComp != nullptr && ImGui::Button("Delete Component"))
		{
			if (selectedCompName == "Renderer")
			{
				world->DeleteRectangleRenderer(selectedObj->GetName());
				selectedObj->DeleteRectangleRenderer();
			}
			if (selectedCompName == "Collider")
			{
				world->DeleteRectangleRenderer(selectedObj->GetName());
				selectedObj->DeleteRectangleCollider();
			}
			if (selectedCompName == "Player Controller")
			{
				world->DeleteRectangleRenderer(selectedObj->GetName());
				selectedObj->DeletePlayerController();
			}
			if (selectedCompName == "Color Changer")
			{
				world->DeleteRectangleRenderer(selectedObj->GetName());
				selectedObj->DeleteCollisionColorChanger();
			}
		}
		//LOL
		if (selectedCompName == "Renderer")
		{
			ImGui::InputInt("Width", &selectedObj->GetRenderer()->width);
			ImGui::InputInt("Height", &selectedObj->GetRenderer()->height);

			ImGui::InputInt("R", &selectedObj->GetRenderer()->originalColor.r);
			ImGui::InputInt("G", &selectedObj->GetRenderer()->originalColor.g);
			ImGui::InputInt("B", &selectedObj->GetRenderer()->originalColor.b);
		}

	}
	else
	{
		ImGui::Text("");
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}
