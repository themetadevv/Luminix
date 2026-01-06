#pragma once

#include "core.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "maths.h"

enum class VideoMode {
	Default = 0,
	Windowed,
	Borderless,
	Fullscreen
};

std::string_view GetVideoModeString(VideoMode vm);

enum class WindowState {
	Default = 0,
	Minimized,
	Maximized,
	Focused
};

struct WindowSpecs {
	std::string Title = "GLFW Context Version : 4.6";
	Vec2<int> Size = { 0, 0 };
	Vec2<int> Position = { 0, 0 };
	VideoMode VidMode = VideoMode::Default;
	WindowState State = WindowState::Default;
	bool VSync = false;
	bool CustomHeader = false;
};

namespace af::window {
	class AF_API Window {
	private:
		WindowSpecs m_WindowSpecs;
		GLFWwindow* m_WindowHandle;
		GLFWmonitor* m_PrimaryMonitorHandle;

		VideoMode  m_OldVideoMode;
		Vec2<int> m_SavedWindowSize;
		Vec2<int> m_SavedWindowedPosition;

		bool m_Running;

	private:
		void SaveWindowedSizePos();

	public:
		Window(const WindowSpecs& window_specs = WindowSpecs());
		~Window();

	public:
		// <------------------ Setters ------------------>

		void SetWindowSize(const Vec2<int>& size);
		void SetWindowPosition(const Vec2<int>& pos);
		void SetVSync(bool val);

		void SetVideoMode(VideoMode vm);
		void SetWindowState(WindowState ws);

	public:
		// <------------------ Getters ------------------>

		std::string_view GetWindowTitle() const { return m_WindowSpecs.Title; }

		Vec2<int> GetWindowSize() const { return m_WindowSpecs.Size; }
		Vec2<int> GetWindowPosition() const { return m_WindowSpecs.Position; }

		VideoMode GetCurrentVideoMode() const { return m_WindowSpecs.VidMode; }
		WindowState GetCurrentWindowState() const { return m_WindowSpecs.State; }

		GLFWwindow* GetNativeWindowHandle() const { return m_WindowHandle; }

		bool IsVSync() { return m_WindowSpecs.VSync; }
		bool IsRunning() { return m_Running; }

	public:
		// <------------------ Functions ------------------>

		void Update();
		void Shutdown();
	};
}

