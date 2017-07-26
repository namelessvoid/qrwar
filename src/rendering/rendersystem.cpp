#include "rendering/rendersystem.hpp"

#include <cassert>

namespace qrw
{

void RenderSystem::startUp()
{
	m_renderables = new std::set<Renderable*>();
}

void RenderSystem::shutDown()
{
	delete m_renderables;
}

void RenderSystem::registerRenderable(Renderable* renderable)
{
	assert(m_renderables!=nullptr);

	m_renderables->insert(renderable);
}

void RenderSystem::deregisterRenderable(Renderable* renderable)
{
	assert(m_renderables!=nullptr);
	m_renderables->erase(renderable);
}

void RenderSystem::renderAll(sf::RenderTarget& renderTarget)
{
	for(Renderable* renderable : *m_renderables)
	{
		renderable->render(renderTarget);
	}
}

} // namespace qrw
