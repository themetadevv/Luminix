#pragma once

#include "core.h"

#include <string>

// Creds : Cherno

namespace Luminix {
	class LX_API Layer {
	public:
		Layer(std::string_view layer_name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(double dt) {};
		virtual void OnRender() {};
		virtual void OnEditorRender() {};

		std::string GetLayerName() const { return m_LayerName; }

	protected:
		std::string m_LayerName;
	};
}