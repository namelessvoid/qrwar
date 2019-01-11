#include <gtest/gtest.h>

#include "rendering/renderablezindexcomparer.hpp"

#include "__mocks__/rendering/renderablemock.hpp"

using ::testing::ElementsAre;

TEST(RenderableZIndexComparer_Compare, If_first_z_index_is_less_than_second_z_index_Then_true_is_returned)
{
	qrw::RenderableZIndexComparer comparer;

	RenderableMock a(0);
	a.setZIndex(12);

	RenderableMock b(0);
	b.setZIndex(13);

	ASSERT_TRUE(comparer(&a, &b));
	ASSERT_FALSE(comparer(&b, &a));
}

TEST(RenderableZIndexComparer_Compare, Is_compatible_to_std_sort)
{
	// Arrange
	qrw::RenderableZIndexComparer comparer;

	RenderableMock a(0);
	a.setZIndex(12);

	RenderableMock b(0);
	b.setZIndex(13);

	RenderableMock c(0);
	c.setZIndex(14);

	std::vector<qrw::Renderable*> renderables = {&b, &c, &a};

	// Act
	std::sort(renderables.begin(), renderables.end(), comparer);

	// Assert
	ASSERT_THAT(renderables, ElementsAre(&a, &b, &c));
}
