#include "rendering/rendersystem.hpp"

#include <cassert>
#include <vector>
#include <algorithm>

#include "rendering/renderablezindexcomparer.hpp"

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
	renderables_.clear();
}

void RenderSystem::registerRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	renderables_[renderable->getLayer()].insert(renderable);
}

void RenderSystem::deregisterRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	renderables_[renderable->getLayer()].erase(renderable);
}

void RenderSystem::renderAll()
{
	camera_->applyTo(*renderTarget_);

	RenderableZIndexComparerLess zIndexComparer;
	for(auto& layer : renderables_)
	{
		if(layer.second.empty()) continue;

		std::vector<Renderable*> orderedRenderables(layer.second.begin(), layer.second.end());
		std::sort(orderedRenderables.begin(), orderedRenderables.end(), zIndexComparer);

		for(auto& renderable : orderedRenderables)
		{
			if (renderable->isVisible())
				renderable->render(*renderTarget_);
		}
	}
}

} // namespace qrw
