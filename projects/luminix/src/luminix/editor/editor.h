#pragma once

#include "core.h"
#include "maths.h"

#include "editor_enums.h"
#include "../window/window.h"

namespace Luminix {
	LX_API bool BeginUIContainer(const char* title, bool* open = (bool*)0, WindowFlags flags = WindowFlags::WindowFlags_None);
	LX_API void EndUIContainer();

	LX_API bool Button(const char* label, Vec2<float> size = { 0.0f, 0.0f });
	LX_API void Text(const Color& color, const char* fmt, ...);

	LX_API bool InputText(const char* label, char* v, size_t size);

	LX_API bool InputFloat(
		const char* label,
		float* v,
		const char* format = "%.3f",
		float step = 0.0f,
		float step_fast = 0.0f,
		InputTextFlags flags = InputTextFlags::InputTextFlags_None
	);

	LX_API bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, InputTextFlags flags = InputTextFlags::InputTextFlags_None);

	LX_API bool SliderFloat(
		const char* label,
		float* v,
		float min_v,
		float max_v,
		const char* format = "%.3f",
		SliderFlags flags = SliderFlags::SliderFlags_None
	);

	LX_API bool ComboBox(const char* label, int* slot, const char* items);

	// AF_API void Header(af::window::Window* window, const char* title, float height, const Color& color = Color(45.0f));
}