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
void randomizeWithSeed(std::vector<int>& matrix, int width, int seed);
void randomizeParameter(std::vector<int>& matrix, int& width, int seed, int power, bool bHashEnabled);

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

	int powerOfTwo = 0, seed = 0;
	bool bEnableHash = false;

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

		ImGui::InputInt("Powers of Two", &powerOfTwo, 0, 0);
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip("The power of 2 to set as the size of the matrix. Use 0 for default size: 128x128.");
			ImGui::EndTooltip();
		}

		ImGui::InputInt("Seed", &seed, 0, 0);
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip("The seed value to base the RNG off of. Use 0 for true random number generation.");
			ImGui::EndTooltip();
		}

		ImGui::Checkbox("Enable hashing algorithm seed", &bEnableHash);
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip("Enable this to use szudzik algorithm as the seed. Inputs to algorithm are the coordinates of the matrix.");
			ImGui::EndTooltip();
		}

		if (ImGui::Button("Re-generate"))
		{
			randomizeParameter(matrix, width, seed, powerOfTwo, bEnableHash);
		}

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
}

void randomizeWithSeed(std::vector<int>& matrix, int width, int seed)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
		{
			matrix[y * width + x] = randomWithSeed(seed, 0, 1);
		}
}

void randomizeParameter(std::vector<int>& matrix, int& width, int seed, int power, bool bHashEnabled)
{
	if (power > 0)
	{
		width = pow(2, power);
		matrix.resize(width * width, 0);

	}

	if (bHashEnabled)
	{
		for (int x = 0; x < width; x++)
			for (int y = 0; y < width; y++)
			{
				int szudzikValue = x >= y ? (x * x) + x + y : (y * y) + x;
				int rand = randomWithSeed(szudzikValue, 0, 1);
				matrix[y * width + x] = rand;
			}
	}
	else
	{
		if (seed > 0)
		{
			randomizeWithSeed(matrix, width, seed);
		}
		else
		{
			randomize(matrix, width);
		}
	}

	
}
