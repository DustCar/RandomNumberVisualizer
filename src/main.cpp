#include <iostream>
#include <sstream>
#include <raylib.h>
#include <asserts.h>

#include <imgui.h>
#include <rlImGui.h>
#include <imguiThemes.h>

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

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);

	/* imgui setup begin */
		rlImGuiBegin();

		// removes gray box that covers the game screen
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		// allows docking widgets to main window
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	/* imgui setup end */


		rlImGuiEnd();

		EndDrawing();
	}

	CloseWindow();


#pragma region imgui
	rlImGuiShutdown();
#pragma endregion


	return 0;
}
