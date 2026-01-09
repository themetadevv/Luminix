
#include "lxpch.h"
#include "assertion.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "../input/input.h"

#include "editor.h"

static ImGuiWindowFlags_ GetWindowFlags_ImGuiBackend(WindowFlags wf) {
	return static_cast<ImGuiWindowFlags_>(wf);
}

static ImGuiInputTextFlags_ GetInputTextFlags_ImGuiBackend(InputTextFlags itf) {
	return static_cast<ImGuiInputTextFlags_>(itf);
}

static ImGuiSliderFlags_ GetSliderFlags_ImGuiBackend(SliderFlags sf) {
	return static_cast<ImGuiSliderFlags_>(sf);
}

template <typename T>
static ImVec2 vec2t_to_imvec2(const Vec2<T>& v) {
	return ImVec2(static_cast<T>(v.x), static_cast<T>(v.y));
}

template <typename T>
static Vec2<T> imvec2_to_vec2t(const ImVec2& v) {
	return Vec2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
}

static ImVec4 color_to_imvec4(const Color& color) {
	ImVec4 c(color.R, color.B, color.A, color.A);
	return c;
}

static ImU32 color_to_imu32(const Color& color) {
	return IM_COL32(
		(int)(std::clamp(color.R, 0.0f, 1.0f) * 255.0f),
		(int)(std::clamp(color.G, 0.0f, 1.0f) * 255.0f),
		(int)(std::clamp(color.B, 0.0f, 1.0f) * 255.0f),
		(int)(std::clamp(color.A, 0.0f, 1.0f) * 255.0f)
	);
}

namespace Luminix {
	bool BeginUIContainer(const char* title, bool* open, WindowFlags flags) {
		LX_ASSERT(ImGui::GetCurrentContext() != nullptr, "Setup UIContext before rendering UI");
		if (!ImGui::GetCurrentContext()) return false;

		bool window = ImGui::Begin(title, open, GetWindowFlags_ImGuiBackend(flags));
		return window;
	}

	void EndUIContainer() {
		ImGui::End();
	}

	bool Button(const char* label, Vec2<float> size) {
		return ImGui::Button(label, vec2t_to_imvec2(size));
	}

	void Text(const Color& color, const char* fmt, ...) {
		ImGui::TextColored(color_to_imvec4(color), fmt);
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

	bool InputInt(const char* label, int* v, int step, int step_fast, InputTextFlags flags) {
		return ImGui::InputInt(label, v, step, step_fast, GetInputTextFlags_ImGuiBackend(flags));
	}

	bool SliderFloat(const char* label, float* v, float min_v, float max_v, const char* format, SliderFlags flags) {
		return ImGui::SliderFloat(label, v, min_v, max_v, format, GetSliderFlags_ImGuiBackend(flags));
	}

	bool ComboBox(const char* label, int* current_slot, const char* items) {
		return ImGui::Combo(label, current_slot, items);
	}

	//struct WindowDrag {
	//	bool dragging = false;
	//	Vec2<int> window_position = { 0, 0 };
	//	Vec2<float> mouse_click_position = { 0, 0 };
	//};

	//static WindowDrag s_WindowDrag;

	//void Header(af::window::Window* window, const char* title, float height, const Color& color)
	//{
	//	ImGuiIO& io = ImGui::GetIO();

	//	// setting up window transform to mimic a custom header

	//	ImGuiViewport* view_port = ImGui::GetMainViewport();

	//	ImGui::SetNextWindowPos(view_port->WorkPos);
	//	ImGui::SetNextWindowSize(ImVec2(view_port->WorkSize.x, height));

	//	// creating the window (header)

	//	BeginUIContainer(
	//		title,
	//		nullptr,
	//		NoTitleBar | NoResize | NoMove | NoCollapse
	//	);

	//	ImDrawList* draw = ImGui::GetWindowDrawList();

	//	ImVec2 win_pos = ImGui::GetWindowPos();
	//	ImVec2 win_size = ImGui::GetWindowSize();

	//	ImVec2 rect_min = win_pos;
	//	ImVec2 rect_max = ImVec2(win_pos.x + win_size.x, win_pos.y + win_size.y);
	//	ImU32  rect_color = color_to_imu32(color);

	//	draw->AddRectFilled(
	//		rect_min,
	//		rect_max,
	//		rect_color
	//	);

	//	ImGui::SetCursorScreenPos(win_pos);
	//	ImGui::InvisibleButton("##win_drag_hitbox", win_size);
	//	
	//	/*if (!s_WindowDrag.dragging && ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
	//		s_WindowDrag.dragging = true;

	//		Vec2<int> wp = window->GetWindowPosition();
	//		s_WindowDrag.window_position = Vec2<float>((float)wp.x, (float)wp.y);
	//		s_WindowDrag.mouse_click_position = Vec2<float>(io.MousePos.x, io.MousePos.y);
	//	}*/

	//	Vec2<int> glfw_window_position = {};

	//	if (!s_WindowDrag.dragging && ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
	//		s_WindowDrag.dragging = true;
	//		glfw_window_position = window->GetWindowPosition();
	//		s_WindowDrag.window_position = glfw_window_position;
	//		s_WindowDrag.mouse_click_position.x = io.MousePos.x;
	//		s_WindowDrag.mouse_click_position.y = io.MousePos.y;
	//	}

	//	if (s_WindowDrag.dragging && !ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
	//		s_WindowDrag.dragging = false;
	//	}

	//	if (s_WindowDrag.dragging) {
	//		ImVec2 mouse_delta = ImVec2(io.MousePos.x - s_WindowDrag.mouse_click_position.x, io.MousePos.y - s_WindowDrag.mouse_click_position.y);

	//		window->SetWindowPosition(
	//			Vec2<int>(
	//				(int)(s_WindowDrag.window_position.x + mouse_delta.x),
	//				(int)(s_WindowDrag.window_position.y + mouse_delta.y)
	//			)
	//		);
	//	}

	//	EndUIContainer();
	//}

	

}