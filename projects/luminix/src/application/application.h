#pragma once

#include "core.h"

#include "logger/logger.h"
#include "window/window.h"
#include "time/time.h"
#include "input/input.h"
#include "editor/editor_layer.h"

#include "layer/layer.h"
#include "layer/layer_stack.h"

namespace Luminix {
	struct ApplicationSetting {
		std::string AppName = "Luminix App 1.0";
		WindowState AppState = WindowState::Default;
		VideoMode   AppVideoMode = VideoMode::Default;
		bool AppVSync = false;
		bool AppHeader = false;

		ApplicationSetting() = default;
	};

	class LX_API Application {
	private:
		WindowSetting m_WindowSetting;
		Scope<Window> m_Window;

		LayerStack m_LayerStack;
		uint32_t m_LayerCount = 0;
		
		EditorLayer* m_EditorLayer;
		static Application* m_sApplication;

	public:
		Window& GetWindow() { return *m_Window; }

	public:
		Application(const ApplicationSetting& app_setting = ApplicationSetting());
		virtual ~Application();

	public:
		// methods

		void Run();
		void AddLayer(Layer* layer);
		void AddOverlay(Layer* overlay);

		static Application& Get() { return *m_sApplication; }
	};

	Application* CreateApplication();
}