#pragma once

#include "core.h"
#include "maths.h"
#include "application/window/window.h"
#include <imgui.h>

#define GLSL_VERSION_3_3 "#version 330"
#define GLSL_VERSION_4_6 "#version 460"

namespace af::ui {
	enum Theme {
		Default = 0,
		Dark,
		Light,
		Classic
	};

	struct UISpecs {
		Theme Theme = Theme::Default;
		bool Dockspace = false;
		const char* GLSL_Version = GLSL_VERSION_4_6; // 4.6 default

		UISpecs() = default;
	};

	class AF_API UIContext {
	private:
		UISpecs m_UISpecs;
		ImGuiContext* m_ImGuiContext;
		af::window::Window* m_Window;

	private:
		bool Init(af::window::Window* window);

	public:
		UIContext(af::window::Window* window, const UISpecs& ui_specs = UISpecs());
		~UIContext();

	public:
		ImGuiContext* GetContext() const { return m_ImGuiContext; }
		
		void BeginRender();
		void EndRender();
	};
}