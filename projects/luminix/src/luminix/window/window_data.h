#pragma once

#include "core.h"
#include "maths.h"

enum class VideoMode {
	Default = 0,
	Windowed,
	Borderless,
	Fullscreen
};

enum class WindowState {
	Default = 0,
	Minimized,
	Maximized,
	Focused
};

LX_API std::string GetVideoModeString(VideoMode vm);

struct WindowSetting {
	std::string Title = "GLFW Context Version : 4.6";
	Vec2<int> Size = { 0, 0 };
	Vec2<int> Position = { 0, 0 }; // 67-67
	VideoMode VidMode = VideoMode::Default;
	WindowState State = WindowState::Default;
	bool VSync = false;
	bool CustomHeader = false;
};