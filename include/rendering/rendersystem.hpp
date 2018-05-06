#ifndef QRW_RENDERSYSTEM_HPP
#define QRW_RENDERSYSTEM_HPP

#include <map>
#include <set>

#include "core/prioritylist.hpp"

#include "rendering/renderable.hpp"
#include "rendering/birdseyecamera.hpp"

namespace qrw
{

class RenderSystem
{
public:
	RenderSystem() {}

	void startUp(sf::RenderTarget& renderTarget);
	void shutDown();

	void registerRenderable(Renderable* renderable);
	void deregisterRenderable(Renderable* renderable);

	void renderAll();

	BirdsEyeCamera& getCamera() const { return *camera_; }

private:
	RenderSystem(const RenderSystem&) = delete;

	PriorityList<Renderable*> renderables_;

	sf::RenderTarget* renderTarget_;

	BirdsEyeCamera* camera_;
};

extern RenderSystem g_renderSystem;

} // namespace qrw

#endif // QRW_RENDERSYSTEM_HPP
