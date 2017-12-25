#ifndef QRW_PATHRENDERCOMPONENT_HPP
#define QRW_PATHRENDERCOMPONENT_HPP

#include "foundation/spritecomponent.hpp"

namespace qrw {

class PathRenderComponent : public SpriteComponent
{
public:
    PathRenderComponent();

    virtual ~PathRenderComponent();

private:
    PathRenderComponent(const PathRenderComponent& rhs) = delete;

    PathRenderComponent& operator=(const PathRenderComponent& rhs) = delete;

    // Renderable interface
public:
    virtual void render(sf::RenderTarget &renderTarget) override;
};


} // namespace qrw

#endif // QRW_PATHRENDERCOMPONENT_HPP
