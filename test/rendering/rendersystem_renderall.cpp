#include <gtest/gtest.h>

#include <SFML/Graphics/RenderTexture.hpp>

#include "rendering/rendersystem.hpp"

#include "__mocks__/rendering/renderablemock.hpp"

using ::testing::_;
using ::testing::Sequence;

TEST(RenderSystem_RenderAll, Then_z_index_of_renderables_are_accounted_for)
{
	// Arrange
	sf::RenderTexture texture;
	qrw::RenderSystem renderSystem;
	renderSystem.startUp(texture);

	RenderableMock a(0);
	a.setZIndex(13);
	renderSystem.registerRenderable(&a);

	RenderableMock b(0);
	b.setZIndex(12);
	renderSystem.registerRenderable(&b);

	// Assert
	Sequence renderSequence;
	EXPECT_CALL(b, render(_)).InSequence(renderSequence);
	EXPECT_CALL(a, render(_)).InSequence(renderSequence);

	// Act
	renderSystem.renderAll();

	// Clean up
	renderSystem.shutDown();
}
