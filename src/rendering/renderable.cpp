#include "rendering/renderable.hpp"

#include "rendering/rendersystem.hpp"

namespace qrw
{

Renderable::Renderable(Layer layer)
	: layer_(layer),
	  zIndex_(0),
	  visible_(true)
{
	g_renderSystem.registerRenderable(this);
}

Renderable::~Renderable()
{
	g_renderSystem.deregisterRenderable(this);
}

Layer Renderable::getLayer()
{
	return layer_;
}

} // namespace qrw
