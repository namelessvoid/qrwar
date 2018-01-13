#include "rendering/rendersystem.hpp"

#include <cassert>

namespace qrw
{

void RenderSystem::startUp(sf::RenderTarget& renderTarget)
{
	renderTarget_ = &renderTarget;
	camera_ = new BirdsEyeCamera();
}

void RenderSystem::shutDown()
{
	delete camera_;
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

void RenderSystem::renderAll()
{
	camera_->applyTo(*renderTarget_);
	for(auto layerIterator = m_renderables.begin(); layerIterator != m_renderables.end(); ++layerIterator)
	{
		for(Renderable* renderable : layerIterator->second)
		{
			if(renderable->isVisible())
				renderable->render(*renderTarget_);
		}
	}
}

} // namespace qrw
