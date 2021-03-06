#include "game/pathrendercomponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/board.hpp"
#include "engine/pathfinding/path.hpp"

#include "gui/texturemanager.hpp"
#include "gui/scene.hpp"

#include "game/path.hpp"
#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/structure.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

PathRenderComponent::PathRenderComponent(Path& owner)
	: SpriteComponent(owner, RENDER_LAYER_PATH)
{
	setPath(nullptr);
	setTexture(TextureManager::getInstance()->getTexture("footstep"));
	setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
}

void qrw::PathRenderComponent::render(sf::RenderTarget &renderTarget)
{
	if(!isVisible())
		return;

	const int pathLength = path_->getLength();

	const Coordinates* previous = nullptr;
	const Coordinates* current  = &path_->getStep(0);
	const Coordinates* next     = &path_->getStep(1);

	auto board = g_scene.findSingleGameObject<Board>();

	// Do not render first step.
	for(int i = 1; i < pathLength; ++i)
	{
		previous = current;
		current  = next;

		// Reset the previously applied transformations.
		_rectangle->setOrigin(0.5f * SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
		_rectangle->setScale(1, 1);
		_rectangle->setRotation(0);

		// Transformations relative to the previous step
		Coordinates prevDelta(*previous - *current);
		if(prevDelta.getX() != 0)
			_rectangle->rotate(-90 * prevDelta.getX());
		if(prevDelta.getY() != 0)
			_rectangle->scale(1, prevDelta.getY());

		// Transformations relative to the next step (if possible)
		if(i < pathLength - 1)
		{
			next = &path_->getStep(i+1);

			Coordinates prevNextDelta(*previous - *next);

			// If the path has a corner at this position
			if(prevNextDelta.getX() != 0 && prevNextDelta.getY() != 0)
			{
				int rotationdirection = 0;
				// horizontal
				if(prevDelta.getX() == 0)
				{
					rotationdirection = -1;
				}
				// vertical
				else if(prevDelta.getY() == 0)
				{
					rotationdirection = +1;
				}
				_rectangle->rotate(rotationdirection * 45 * (prevNextDelta.getX() * prevNextDelta.getY()));
			}
		}

		float yOffset{0.0f};
		if(board) {
			if(auto structure = board->getStructure(*current)) {
				yOffset = structure->getCurrentVisualHeightForUnits();
			}
		}

		sf::Vector2f worldPosition{SQUARE_DIMENSION * (0.5f + current->getX()), SQUARE_DIMENSION * (0.5f + current->getY())};
		sf::Vector2f isoPosition = worldToIso(worldPosition) + sf::Vector2f(0, yOffset);
		_rectangle->setPosition(isoPosition);

		renderTarget.draw(*_rectangle);
	} // for(step in path)
}

void PathRenderComponent::setPath(const pathfinding::Path *path)
{
	path_ = path;

	setVisible(path != nullptr);
}

} // namespace qrw
