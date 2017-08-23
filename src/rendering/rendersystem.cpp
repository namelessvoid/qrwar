#include "rendering/rendersystem.hpp"

#include <cassert>

namespace qrw
{

void RenderSystem::startUp()
{
}

void RenderSystem::shutDown()
{
	m_renderables.clear();
}

void RenderSystem::registerRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	m_renderables[renderable->getLayer()].insert(renderable);
}

void RenderSystem::deregisterRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	m_renderables[renderable->getLayer()].erase(renderable);
}

void RenderSystem::renderAll(sf::RenderTarget& renderTarget)
{
	for(auto layerIterator = m_renderables.begin(); layerIterator != m_renderables.end(); ++layerIterator)
	{
		for(Renderable* renderable : layerIterator->second)
		{
			if(renderable->isVisible())
				renderable->render(renderTarget);
		}
	}
}

} // namespace qrw
