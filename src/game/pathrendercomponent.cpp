#include "game/pathrendercomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

PathRenderComponent::PathRenderComponent()
	: SpriteComponent(RENDER_LAYER_PATH)
{
}

PathRenderComponent::~PathRenderComponent()
{
}

} // namespace qrw


void qrw::PathRenderComponent::render(sf::RenderTarget &renderTarget)
{
}
