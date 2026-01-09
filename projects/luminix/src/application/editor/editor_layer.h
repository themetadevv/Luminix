#pragma once

#include "core.h"
#include "maths.h"

#include "../layer/layer.h"

#include <imgui.h>

#define GLSL_VERSION_3_3 "#version 330"
#define GLSL_VERSION_4_6 "#version 460"

namespace Luminix {
	struct EditorSetting {
		enum EditorTheme {
			EditorThemeDefault = 0,
			EditorThemeDark,
			EditorThemeLight,
			EditorThemeClassic
		};

		EditorTheme Theme = EditorTheme::EditorThemeDefault;

		const char* GL_Version = GLSL_VERSION_4_6; // 4.6 default

		bool Dockspace = false;

		EditorSetting() = default;
	};

	class LX_API EditorLayer : public Layer {
	private:
		EditorSetting m_EditorSetting;
		ImGuiContext* m_ImGuiContext;

	public:
		EditorLayer(const EditorSetting& setting = EditorSetting());
		~EditorLayer() = default;

	public:
		ImGuiContext* GetContext() const { return m_ImGuiContext; }
		
		void BeginRender();
		void EndRender();

	public:
		void OnAttach() override;
		void OnDetach() override;
	};
}