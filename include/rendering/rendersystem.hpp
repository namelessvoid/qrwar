#ifndef QRW_RENDERSYSTEM_HPP
#define QRW_RENDERSYSTEM_HPP

#include <set>

#include "rendering/renderable.hpp"

namespace qrw
{

class RenderSystem
{
public:
	RenderSystem() {}

	void startUp();
	void shutDown();

	void registerRenderable(Renderable* renderable);
	void deregisterRenderable(Renderable* renderable);

	void renderAll(sf::RenderTarget& renderTarget);

private:
	RenderSystem(const RenderSystem&) = delete;

	std::set<Renderable*>* m_renderables;
};

extern RenderSystem g_renderSystem;

} // namespace qrw

#endif // QRW_RENDERSYSTEM_HPP
