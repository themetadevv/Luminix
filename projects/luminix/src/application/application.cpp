
#include "lxpch.h"
#include "logger/logger.h"
#include "application.h"

namespace Luminix {
	Application* Application::m_sApplication = nullptr;

	Application::Application(const ApplicationSetting& app_setting)
	{
		m_WindowSetting.Title = app_setting.AppName;
		m_WindowSetting.Size = { 1600, 900 };
		m_WindowSetting.VSync = app_setting.AppVSync;
		m_WindowSetting.CustomHeader = app_setting.AppHeader;

		m_sApplication = this;
		m_Window = CreateScope<Window>(m_WindowSetting);
		Time::Init();
		Input::Init(static_cast<GLFWwindow*>(m_Window->GetNativeWindowHandle()));

		EditorSetting setting;
		m_EditorLayer = new EditorLayer(setting);
		AddOverlay(m_EditorLayer);
	}

	Application::~Application() {
		m_sApplication = nullptr;
		m_Window->Shutdown();
	}

	void Application::Run() {
		while (m_Window->IsRunning()) {
			m_EditorLayer->BeginRender();

			for (Layer* layers : m_LayerStack) {
				layers->OnRender();
				layers->OnUpdate(Time::GetDeltaTime());
				layers->OnEditorRender();
			}
				
			Time::Update();
			Input::Update();
			m_Window->Update();
			m_EditorLayer->EndRender();
		}
	}

	void Application::AddLayer(Layer* layer) {
		m_LayerStack.AddLayer(layer);
		layer->OnAttach();
		m_LayerCount++;
	}

	void Application::AddOverlay(Layer* overlay) {
		m_LayerStack.AddOverlay(overlay);
		overlay->OnAttach();
		m_LayerCount++;
	}
}