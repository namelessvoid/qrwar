#ifndef QRW_BOARDBACKGROUNDCOMPONENT_HPP
#define QRW_BOARDBACKGROUNDCOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "rendering/renderable.hpp"

#include "engine/board.hpp"

#include "foundation/gamecomponent.hpp"

namespace qrw
{

class BoardBackgroundComponent : public GameComponent, public Renderable
{
public:
	explicit BoardBackgroundComponent(Board& owner);

	void render(sf::RenderTarget& renderTarget) override;

	void setPosition(const sf::Vector2f& position) override;

	const sf::Vector2f& getPosition() const override;

	sf::Vector2f getCenter() const;

private:
	sf::Sprite plainSquareSprite_;

	Board& owner_;
};

} // namespace qrw

#endif //QRW_BOARDBACKGROUNDCOMPONENT_HPP
