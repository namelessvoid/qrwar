#ifndef QRW_TEST_RENDERABLEMOCK_HPP
#define QRW_TEST_RENDERABLEMOCK_HPP

#include "rendering/renderable.hpp"

class RenderableMock : public qrw::Renderable
{
public:
	explicit RenderableMock(qrw::Layer layer)
		: qrw::Renderable(layer)
	{}

	void render(sf::RenderTarget& renderTarget) override
	{
		throw "not implemented";
	}

	void setPosition(const sf::Vector2f& position) override
	{
		throw "not implemented";
	}

	const sf::Vector2f& getPosition() const override
	{
		throw "not implemented";
	}
};

#endif //QRW_TEST_RENDERABLEMOCK_HPP
