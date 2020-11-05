#pragma once

#include "../Framework/Window.h"
#include "../Framework/Utility/MorTimer.h"
#include "../Framework/Drawable/Drawable.h"
#include "../Framework/Surface.h"
#include "../Framework/Managers/ImGuiManager.h"
#include "../Framework/Camera.h"
#include <set>
#include "Board.h"
#include "Snaek.h"

class App
{
public:
	App();
	App( const App& ) = delete;
	App& operator=( const App& ) = delete;
	~App();
	int Go();
private:
	void DoFrame();
	void ImGuiWindows() noexcept;
	void SpawnSimulationWindow() noexcept;
	void SpawnDrawableControlWindowMangerWindow() noexcept;
	void SpawnDrawableControlWindows() noexcept;
private:
	float c[3] = { 0.1f,0.0f,0.1f };
	ImGuiManager imgui;
	Camera cam;
	Window wnd;
	MorTimer timer;
	Board brd;
	Snek snek;
	float SimulationSpeed = 1.0f;
	bool paused = false;
	std::set<int> DrawableId;
	std::optional<int> index;
	std::optional<int> TypeIndex;
	Vei2 dir = { 0,0 };
	float deltaTime = 0.0f;
	static constexpr float SleepTime = 0.25f;
	bool GameOver = false;
};