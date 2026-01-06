#pragma once

#include "core.h"
#include "maths.h"
#include "ui_enums.h"

namespace af::ui {
	AF_API bool BeginUIContainer(const char* title, bool* open = (bool*)0, WindowFlags flags = WindowFlags::WindowFlags_None);
	AF_API void EndUIContainer();

	AF_API bool Button(const char* label, Vec2<float> size = { 0.0f, 0.0f });
	AF_API void Text(const Color& color, const char* fmt, ...);

	AF_API bool InputText(const char* label, char* v, size_t size);

	AF_API bool InputFloat(
		const char* label,
		float* v,
		const char* format = "%.3f",
		float step = 0.0f,
		float step_fast = 0.0f,
		InputTextFlags flags = InputTextFlags::InputTextFlags_None
	);

	AF_API bool SliderFloat(
		const char* label,
		float* v,
		float min_v,
		float max_v,
		const char* format = "%.3f",
		SliderFlags flags = SliderFlags::SliderFlags_None
	);
}