#ifndef QRW_TEXTUREALPHAMASK_HPP
#define QRW_TEXTUREALPHAMASK_HPP

#include <SFML/Graphics/Texture.hpp>

namespace qrw {

/**
 * This class is inspired by the pixel perfect collision detection SFML tutorial:
 * https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
 * Especially the ctor and isPixelSet() are taken from there.
 */
class TextureAlphaMask
{
public:
	/**
	 * Constructs a new TextureAlphaMask for the provided texture.
	 * @param texture The texture represented by this TextureAlphaMask.
	 */
	explicit TextureAlphaMask(const sf::Texture& texture);

	~TextureAlphaMask() = default;

	TextureAlphaMask(const TextureAlphaMask& rhs) = delete;
	TextureAlphaMask& operator=(const TextureAlphaMask& rhs) = delete;

	bool isPixelSet(unsigned int x, unsigned int y) const;

private:
	std::vector<sf::Uint8> pixels_;
	sf::Vector2u size_;
};


} // namespace qrw

#endif // QRW_TEXTUREALPHAMASK_HPP
