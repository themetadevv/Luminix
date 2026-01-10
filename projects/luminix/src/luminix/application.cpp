
#include "lxpch.h"
#include "assertion.h"
#include "application.h"

#include "lxgl/buffers/vbo.h"
#include "lxgl/buffers/vao.h"
#include "lxgl/buffers/ebo.h"

#include "lxgl/lxgl.h"

float vertices[] = {
	// x,    y,    u,   v
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f
};


unsigned int indices[] = {
	0, 3, 2,
	2, 1, 0
};

namespace Luminix {
	Application* Application::m_sApplication = nullptr;

	Application::Application(const ApplicationSetting& app_setting)
	{
		m_WindowSetting.Title = app_setting.AppName;
		m_WindowSetting.Size = { 1600, 900 };
		m_WindowSetting.State = app_setting.AppState;
		m_WindowSetting.VidMode = app_setting.AppMode;
		m_WindowSetting.VSync = app_setting.AppVSync;
		m_WindowSetting.CustomHeader = app_setting.AppHeader;

		m_sApplication = this;
		m_Window = CreateScope<Window>(m_WindowSetting);
		m_AudioDevice = CreateScope<AudioDevice>(nullptr); // nullptr = default sound device

		Time::Init();
		Input::Init(static_cast<GLFWwindow*>(m_Window->GetNativeWindowHandle()));

		EditorSetting setting;
		setting.Theme = EditorSetting::EditorThemeDark;
		setting.EnableDockspace = LX_FALSE;
		setting.EnableGamepad   = LX_TRUE;
		setting.EnableKeyboard  = LX_TRUE;
		setting.EnableViewports = LX_TRUE;
		m_EditorLayer = new EditorLayer(setting);
		AddOverlay(m_EditorLayer);
	}

	Application::~Application() {
		m_sApplication = nullptr;
		if(m_Window->IsRunning())
			m_Window->Shutdown();
	}

	void Application::Run() {
		Ref<LXGL::VertexBuffer> vbo = CreateRef<LXGL::VertexBuffer>(sizeof(vertices), vertices);
		LXGL::AttributeLayout l = LXGL::AttributeLayout(LXGL::AttributeType::Float2, true );
		LXGL::BufferLayout buffer_layout;
		buffer_layout.AddAttribute(l);
		vbo->SetLayout(buffer_layout);

		LXGL::VertexArray* vao = new LXGL::VertexArray();
		vao->AddVertexBuffer(vbo);

		Ref<LXGL::ElementBuffer> ebo = CreateRef<LXGL::ElementBuffer>(6, indices);

		vao->SetElementBuffer(ebo);

		while (m_Window->IsRunning()) {
			m_EditorLayer->SetMenubarCallback(m_EditorMenubarCallback);
			m_EditorLayer->RenderEditor();

			vao->Bind();
			Draw(6);

			for (Layer* layers : m_LayerStack) {
				layers->OnRender();
				layers->OnUpdate(Time::GetDeltaTime());
				layers->OnEditorRender();
			}
				
			Time::Update();
			Input::Update();
			m_Window->Update();
			m_EditorLayer->EndEditor();
		}

		delete vao;
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

	void Application::SetEditorMenubarCallback(const std::function<void()> callback) {
		m_EditorMenubarCallback = callback;
	}

}