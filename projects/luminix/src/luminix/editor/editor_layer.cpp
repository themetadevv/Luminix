
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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		switch (m_EditorSetting.Theme) {
		case EditorSetting::EditorTheme::EditorThemeDefault: ImGui::StyleColorsDark(); break;
		case EditorSetting::EditorTheme::EditorThemeDark: ImGui::StyleColorsDark(); break;
		case EditorSetting::EditorTheme::EditorThemeLight: ImGui::StyleColorsLight(); break;
		case EditorSetting::EditorTheme::EditorThemeClassic: ImGui::StyleColorsClassic(); break;
		}

		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow().GetNativeWindowHandle(), true);
		ImGui_ImplOpenGL3_Init(m_EditorSetting.GL_Version);
	}

	void EditorLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		if (m_ImGuiContext) {
			ImGui::DestroyContext(m_ImGuiContext);
			m_ImGuiContext = nullptr;
		}
	}

	void EditorLayer::BeginRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void EditorLayer::EndRender() {
		Application& app = Application::Get();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(app.GetWindow().GetNativeWindowHandle(), &display_w, &display_h);
		// temporary setting viewport and clearing color buffer bit
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}