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
	renderables_.clear();
}

void RenderSystem::registerRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	renderables_.insert(renderable->getLayer(), renderable);
}

void RenderSystem::deregisterRenderable(Renderable* renderable)
{
	assert(renderable!=nullptr);

	renderables_.erase(renderable->getLayer(), renderable);
}

void RenderSystem::renderAll()
{
	camera_->applyTo(*renderTarget_);
	for(auto& renderable : renderables_)
	{
		if(renderable->isVisible())
			renderable->render(*renderTarget_);
	}
}

} // namespace qrw
