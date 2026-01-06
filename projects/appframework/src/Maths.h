#pragma once

#include <format>
#include "core.h"

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using Mat4 = glm::mat4;

template <typename T>
using Vec1 = glm::tvec1<T>;

template <typename T>
using Vec2 = glm::tvec2<T>;

template <typename T>
using Vec3 = glm::tvec3<T>;

template <typename T>
using Vec4 = glm::tvec4<T>;

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec4<T>& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}

template <typename T>
struct std::formatter<Vec2<T>> {
	 constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vec2<T>& v, std::format_context& ctx) const {
        return std::format_to(
            ctx.out(),
            "({}, {})",
            v.x, v.y
        );
    }
};

template <typename T>
struct std::formatter<Vec3<T>> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Vec3<T>& v, std::format_context& ctx) const {
		return std::format_to(
			ctx.out(),
			"({}, {}, {})",
			v.x, v.y, v.z
		);
	}
};

template <typename T>
struct std::formatter<Vec4<T>> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Vec4<T>& v, std::format_context& ctx) const {
		return std::format_to(
			ctx.out(),
			"({}, {}, {}, {})",
			v.x, v.y, v.z, v.w
		);
	}
};

struct Transform2D {
	Vec2<float> Size;
	Vec2<float> Position;
	float Rotation;

	Transform2D() : Size(0.0f), Position(0.0f), Rotation(0.0f) {}

	Mat4 GetModelMatrix() const {
		Mat4 model_matrix = Mat4(1.0f);
		model_matrix = glm::translate(model_matrix, Vec3<float>(Position, 0.0f));
		model_matrix = glm::rotate(model_matrix, glm::radians(Rotation), Vec3<float>(0.0f, 0.0f, 1.0f));
		model_matrix = glm::scale(model_matrix, glm::vec3(Size, 0.0f));

		return model_matrix;
	}
};

struct Color {
	float R, G, B, A;

	Color() : R(1.0f), G(1.0f), B(1.0f), A(1.0f) {}
	Color(float V) : R(V / 255.0f), G(V / 255.0f), B(V / 255.0f), A(1.0f) {}
	Color(float r, float g, float b) : R(r / 255.0f), G(g / 255.0f), B(b / 255.0f), A(1.0f) {}
	Color(float r, float g, float b, float a) : R(r / 255.0f), G(g / 255.0f), B(b / 255.0f), A(a / 255.0f) {}
};