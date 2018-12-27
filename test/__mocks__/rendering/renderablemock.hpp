#ifndef QRW_TEST_RENDERABLEMOCK_HPP
#define QRW_TEST_RENDERABLEMOCK_HPP

#include <gmock/gmock.h>
#include <SFML/Graphics/RenderTarget.hpp>

#include "rendering/renderable.hpp"

class RenderableMock : public qrw::Renderable {
public:
	explicit RenderableMock(qrw::Layer layer)
			: qrw::Renderable(layer)
	{}

	MOCK_CONST_METHOD0(getPosition, const sf::Vector2f&());
	MOCK_CONST_METHOD0(getZIndex, float());
	MOCK_METHOD1(setPosition, void(const sf::Vector2f&));
	MOCK_METHOD1(render, void(sf::RenderTarget&));
};

#endif //QRW_TEST_RENDERABLEMOCK_HPP
