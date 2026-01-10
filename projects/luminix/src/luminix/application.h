#pragma once

#include "lxcore.h"

#include "logger.h"
#include "window/window.h"
#include "time/time.h"
#include "input/input.h"
#include "audio/audio_device.h"
#include "editor/editor_layer.h"

#include "layer/layer.h"
#include "layer/layer_stack.h"

#define APP_MODE_DEFAULT    (Luminix::VideoMode)0
#define APP_MODE_WINDOWED   (Luminix::VideoMode)1
#define APP_MODE_BORDERLESS (Luminix::VideoMode)2
#define APP_MODE_FULLSCREEN (Luminix::VideoMode)3

#define APP_STATE_DEFAULT   (Luminix::WindowState)0
#define APP_STATE_MINIMIZED (Luminix::WindowState)1
#define APP_STATE_MAXIMIZED (Luminix::WindowState)2
#define APP_STATE_FOCUSED   (Luminix::WindowState)3

#define LX_TRUE 1
#define LX_FALSE 0

namespace Luminix {
	struct ApplicationSetting {
		std::string AppName = "Luminix App 1.0";
		WindowState AppState = WindowState::Default;
		VideoMode AppMode = VideoMode::Default;
		bool AppVSync = LX_FALSE;
		bool AppHeader = LX_FALSE;

		ApplicationSetting() = default;
	};

	class LX_API Application {
	private:
		WindowSetting m_WindowSetting;
		Scope<Window> m_Window;
		Scope<AudioDevice> m_AudioDevice;

		LayerStack m_LayerStack;
		uint32_t m_LayerCount = 0;
		
		EditorLayer* m_EditorLayer;
		std::function<void()> m_EditorMenubarCallback;

		static Application* m_sApplication;

	public:
		Window& GetWindow() { return *m_Window; }
		AudioDevice& GetAudioDevice() { return *m_AudioDevice; }

	public:
		Application(const ApplicationSetting& app_setting = ApplicationSetting());
		virtual ~Application();

	public:
		// methods

		void Run();
		void AddLayer(Layer* layer);
		void AddOverlay(Layer* overlay);
		void SetEditorMenubarCallback(const std::function<void()> callback);

		static Application& Get() { return *m_sApplication; }
	};

	Application* CreateApplication();
}