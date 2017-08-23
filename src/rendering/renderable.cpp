#include "rendering/renderable.hpp"

#include "rendering/rendersystem.hpp"

namespace qrw
{

Renderable::Renderable(Layer layer)
	: m_layer(layer),
	  m_visible(true)
{
	g_renderSystem.registerRenderable(this);
}

Renderable::~Renderable()
{
	g_renderSystem.deregisterRenderable(this);
}

Layer Renderable::getLayer()
{
	return m_layer;
}

} // namespace qrw
