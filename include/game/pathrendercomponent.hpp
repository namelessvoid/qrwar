#ifndef QRW_PATHRENDERCOMPONENT_HPP
#define QRW_PATHRENDERCOMPONENT_HPP

#include "foundation/spritecomponent.hpp"

namespace qrw {

namespace pathfinding {
class Path;
}

class PathRenderComponent : public SpriteComponent
{
public:
    PathRenderComponent();

    virtual ~PathRenderComponent() = default;

	virtual void render(sf::RenderTarget &renderTarget) override;

	void setPath(const pathfinding::Path* path);

private:
    PathRenderComponent(const PathRenderComponent& rhs) = delete;

    PathRenderComponent& operator=(const PathRenderComponent& rhs) = delete;

	const pathfinding::Path* path_;
};


} // namespace qrw

#endif // QRW_PATHRENDERCOMPONENT_HPP
