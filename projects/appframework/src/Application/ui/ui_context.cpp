
#include "afpch.h"
#include "assertion.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_opengl3_loader.h>

#include "ui_context.h"

namespace af::ui {

	UIContext::UIContext(af::window::Window* window, const UISpecs& ui_specs) :
		m_Window(window), m_UISpecs(ui_specs), m_ImGuiContext(nullptr)
	{ 
		Init(window);
	}

	UIContext::~UIContext() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		if (m_ImGuiContext) {
			ImGui::DestroyContext(m_ImGuiContext);
			m_ImGuiContext = nullptr;
		}
	}

	bool UIContext::Init(af::window::Window* window) {
		AF_ASSERT(window != nullptr, "UIContext::Init Called with null Window*");
		if (!window) return false;

		IMGUI_CHECKVERSION();
		m_ImGuiContext = ImGui::CreateContext();
		AF_ASSERT(m_ImGuiContext != nullptr, "Failed to create ImGuiContext!");
		if (!m_ImGuiContext) return false;

		ImGui::SetCurrentContext(m_ImGuiContext);
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		switch (m_UISpecs.Theme) {
			case Theme::Default: ImGui::StyleColorsDark(); break;
			case Theme::Dark: ImGui::StyleColorsDark(); break;
			case Theme::Light: ImGui::StyleColorsLight(); break;
			case Theme::Classic: ImGui::StyleColorsClassic(); break;
		}

		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindowHandle(), true);
		ImGui_ImplOpenGL3_Init(m_UISpecs.GLSL_Version);

		return true;
	}

	void UIContext::BeginRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	void UIContext::EndRender() {
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window->GetNativeWindowHandle(), &display_w, &display_h);


		// temporary setting viewport and clearing color buffer bit

		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}