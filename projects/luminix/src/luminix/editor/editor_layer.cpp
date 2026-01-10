
#include "lxpch.h"
#include "assertion.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3_loader.h>

#include "../application.h"

#include "editor_layer.h"

namespace Luminix {
	EditorLayer::EditorLayer(const EditorSetting& setting)
		: Layer("Editor Layer"), m_ImGuiContext(nullptr), m_EditorSetting(setting)
	{ }

	void EditorLayer::OnAttach() {
		Application& app = Application::Get();

		IMGUI_CHECKVERSION();
		m_ImGuiContext = ImGui::CreateContext();
		LX_ASSERT(m_ImGuiContext != nullptr, "EditorLayer::OnAttach Call Failed! Null ImGuiContext*");

		ImGui::SetCurrentContext(m_ImGuiContext);
		ImGuiIO& io = ImGui::GetIO();

		if(m_EditorSetting.EnableKeyboard)
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		if (m_EditorSetting.EnableGamepad)
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		
		if (m_EditorSetting.EnableViewports)
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		if (m_EditorSetting.EnableDockspace) 
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		switch (m_EditorSetting.Theme) {
			case EditorSetting::EditorTheme::EditorThemeDefault: 
				ImGui::StyleColorsDark(); break;
			case EditorSetting::EditorTheme::EditorThemeDark: 
				ImGui::StyleColorsDark(); break;
			case EditorSetting::EditorTheme::EditorThemeLight: 
				ImGui::StyleColorsLight(); break;
			case EditorSetting::EditorTheme::EditorThemeClassic: 
				ImGui::StyleColorsClassic(); break;
		}

		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow().GetNativeWindowHandle(), true);
		ImGui_ImplOpenGL3_Init(m_EditorSetting.GLVersion);
	}

	void EditorLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		if (m_ImGuiContext) {
			ImGui::DestroyContext(m_ImGuiContext);
			m_ImGuiContext = nullptr;
		}
	}

	void EditorLayer::RenderEditor() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (!m_EditorSetting.EnableDockspace)
			return;

		ImGuiWindowFlags dockspace_window_flag = ImGuiWindowFlags_None;
		dockspace_window_flag |= ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		dockspace_window_flag |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
		dockspace_window_flag |= ImGuiWindowFlags_NoNavFocus;

		if (m_MenubarCallback)
			dockspace_window_flag |= ImGuiWindowFlags_MenuBar;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("DockSpaceRoot", nullptr, dockspace_window_flag)) {
			ImGui::PopStyleVar(3);

			ImGuiID dockspaceID = ImGui::GetID("EditorDockspace");
			ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_None);

			if (m_MenubarCallback) {
				if (ImGui::BeginMenuBar()) {
					m_MenubarCallback();
					ImGui::EndMenuBar();
				}
			}

			ImGui::End();
		}
	}

	void EditorLayer::EndEditor() {
		Application& App = Application::Get();
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(App.GetWindow().GetWindowSize().x, App.GetWindow().GetWindowSize().y);
		ImGui::Render();

		// temporary setting viewport and clearing color buffer bit
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

}