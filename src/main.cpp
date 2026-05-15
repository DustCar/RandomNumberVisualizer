#include <iostream>
#include <sstream>
#include <raylib.h>
#include <asserts.h>
#include <imgui.h>
#include <rlImGui.h>
#include <imguiThemes.h>
#include <vector>
#include "helpers.h"

void randomize(std::vector<int>& matrix, int width);

int main()
{

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif

	const int SCR_WIDTH = 800;
	const int SCR_HEIGHT = 600;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCR_WIDTH, SCR_HEIGHT, "Random Number Visualizer");
	SetExitKey(KEY_NULL);	// Disable ESC from closing window
	SetTargetFPS(240);

#pragma region imgui setup
	rlImGuiSetup(true);

	// set imgui flags
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// Enable Gamepad controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#pragma endregion

	int width = 128;
	std::vector<int> matrix(width * width, 0);

	randomize(matrix, width);

	float zoom = 3.5f;

	while (!WindowShouldClose())
	{
		//======== DRAW ========
		BeginDrawing();
		ClearBackground(BLACK);

		for (int x = 0; x < width; x++)
			for (int y = 0; y < width; y++)
			{
				Color col = matrix[y * width + x] == 0 ? BLACK : WHITE;
				DrawRectangleV({ x * zoom + 10.f, y * zoom + 10.f }, { zoom, zoom }, col);
			}

	/* imgui setup begin */
		rlImGuiBegin();

		// removes gray box that covers the game screen
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		// allows docking widgets to main window
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	/* imgui setup end */

		ImGui::Begin("Randomizer Settings");

		ImGui::Text("True Random Number Generator (TRNG)");
		if (ImGui::Button("Randomize"))
		{
			randomize(matrix, width);
		}
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip("True random. Fully randomizes values using random_device.");
			ImGui::EndTooltip();
		}
		
		ImGui::Separator();
		ImGui::SeparatorText("PARAMETERS");
		ImGui::TextWrapped("In this section, select the parameters desired, then press the button to confirm and randomize the matrix.");

		ImGui::End();


		rlImGuiEnd();

		EndDrawing();
	}

	CloseWindow();


#pragma region imgui
	rlImGuiShutdown();
#pragma endregion


	return 0;
}

void randomize(std::vector<int>& matrix, int width)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
		{
			matrix[y * width + x] = random(0, 1);
		}
};
