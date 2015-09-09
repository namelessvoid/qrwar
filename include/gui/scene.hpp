#ifndef QRW_SCENE_HPP
#define QRW_SCENE_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/board.hpp"

// Foreward declarations
namespace sf
{
class RenderTarget;
}


namespace qrw
{

class Scene
{
public:
	Scene(Board::Ptr board);

	~Scene();

	void render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default);

private:

	sf::RectangleShape _background;
};

} // namespace qrw

#endif // QRW_SCENE_HPP
