#pragma once

#include "core.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "maths.h"
#include "window_data.h"

namespace Luminix {
	class LX_API Window {
	private:
		WindowSetting m_WindowSpecs;
		GLFWwindow* m_WindowHandle;
		GLFWmonitor* m_PrimaryMonitorHandle;

		VideoMode  m_OldVideoMode;

		Vec2<int> m_WindowPosition;
		Vec2<int> m_SavedWindowSize;
		Vec2<int> m_SavedWindowedPosition;

		bool m_Running;

	private:
		void SaveWindowedSizePos();

	public:
		Window(const WindowSetting& window_specs = WindowSetting());
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

		Vec2<int> GetWindowSize() const;
		Vec2<int> GetWindowPosition() const;

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

