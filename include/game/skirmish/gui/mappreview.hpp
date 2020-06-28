#ifndef QRW_MAPPREVIEW_HPP
#define QRW_MAPPREVIEW_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/widget.hpp"

namespace qrw {

class MapPreview : public namelessgui::Widget
{
public:
	MapPreview();

	~MapPreview() = default;

	MapPreview(const MapPreview& rhs) = delete;
	MapPreview& operator=(const MapPreview& rhs) = delete;

	void setSize(const sf::Vector2f& size) override;

	sf::Vector2f getSize() const override;

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	void setTexture(const sf::Texture& texture);

	void render(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void updateRectangle();

	sf::Vector2f size_;
	sf::Vector2f position_;

	std::unique_ptr<sf::RectangleShape> rect_;
};


} // namespace qrw

#endif // QRW_MAPPREVIEW_HPP
