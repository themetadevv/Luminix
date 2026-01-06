
#include "afpch.h"
#include "assertion.h"

#include <imgui.h>
#include "ui.h"

static ImGuiWindowFlags_ GetWindowFlags_ImGuiBackend(WindowFlags wf) {
	return static_cast<ImGuiWindowFlags_>(wf);
}

static ImGuiInputTextFlags_ GetInputTextFlags_ImGuiBackend(InputTextFlags itf) {
	return static_cast<ImGuiInputTextFlags_>(itf);
}

static ImGuiSliderFlags_ GetSliderFlags_ImGuiBackend(SliderFlags sf) {
	return static_cast<ImGuiSliderFlags_>(sf);
}

static ImVec2 GetImVec2(const Vec2<float>& v) {
	return ImVec2(v.x, v.y);
}

static ImVec4 GetColor(const Color& color) {
	ImVec4 clr = ImVec4(color.R, color.G, color.B, color.A);
	return clr;
}

namespace af::ui {
	bool BeginUIContainer(const char* title, bool* open, WindowFlags flags) {
		AF_ASSERT(ImGui::GetCurrentContext() != nullptr, "Setup UIContext before rendering UI");
		if (!ImGui::GetCurrentContext()) return false;

		bool window = ImGui::Begin(title, open, GetWindowFlags_ImGuiBackend(flags));
		return window;
	}

	void EndUIContainer() {
		ImGui::End();
	}

	bool Button(const char* label, Vec2<float> size) {
		return ImGui::Button(label, GetImVec2(size));
	}

	void Text(const Color& color, const char* fmt, ...) {
		ImGui::TextColored(GetColor(color), fmt);
	}

	bool Input(const char* label, float* v) {
		return ImGui::InputFloat(label, v);
	}

	bool InputText(const char* label, char* v, size_t size) {
		return ImGui::InputText(label, v, size);
	}

	bool InputFloat(const char* label, float* v, const char* format, float step, float step_fast, InputTextFlags flags) {
		return ImGui::InputFloat(label, v, step, step_fast, format, GetInputTextFlags_ImGuiBackend(flags));
	}

	bool SliderFloat(const char* label, float* v, float min_v, float max_v, const char* format, SliderFlags flags) {
		return ImGui::SliderFloat(label, v, min_v, max_v, format, GetSliderFlags_ImGuiBackend(flags));
	}

}