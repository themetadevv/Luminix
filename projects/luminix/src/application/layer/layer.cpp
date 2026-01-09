
#include "lxpch.h"
#include "assertion.h"

#include "layer.h"

namespace Luminix {
	Layer::Layer(std::string_view layer_name)
		: m_LayerName(layer_name)
	{
	}
}