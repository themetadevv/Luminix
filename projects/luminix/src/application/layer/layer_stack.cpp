
#include "lxpch.h"
#include "assertion.h"

#include "layer_stack.h"	

namespace Luminix {
	LayerStack::~LayerStack() {
		for (Layer* layers : m_Layers) {
			layers->OnDetach();
			delete layers;
		}
	}

	void LayerStack::AddLayer(Layer* layer) {
		m_Layers.push_back(layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::DestroyLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::AddOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::DestroyOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}	
}