#include "physics/texturealphamask.hpp"

namespace qrw
{

TextureAlphaMask::TextureAlphaMask(const sf::Texture& texture)
{
	size_ = texture.getSize();
	pixels_.resize(size_.x * size_.y);

	sf::Image image = texture.copyToImage();
	for (unsigned int y = 0; y < size_.y; ++y)
	{
		for (unsigned int x = 0; x < size_.x; ++x)
			pixels_[x + y * size_.x] = image.getPixel(x, y).a;
	}
}

bool TextureAlphaMask::isPixelSet(unsigned int x, unsigned int y)
{
	if (x > size_.x || y > size_.y)
		return false;

	return pixels_[x + y * size_.x] > 0;
}

} // namespace qrw
