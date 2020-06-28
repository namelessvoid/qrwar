#ifndef QRW_STRUCTURE_HPP
#define QRW_STRUCTURE_HPP

#include "game/skirmish/coordinates.hpp"
#include "foundation/gameobject.hpp"

namespace sf
{
class Texture;
}

namespace qrw
{
class SpriteComponent;

class Structure : public GameObject
{
friend class StructureMetaClass;

public:
	enum class Type { WALL, STAIRS };

	Structure() = default;

	void onAddToScene() override;
	void initialize() override;
	void onDestroy() override;

	virtual void setPosition(const Coordinates& position);
	const Coordinates& getPosition() const { return position_; }

	virtual void computeTexture() {}

	// Used to display an icon for this structure in the SquareDetailWindow.
	virtual const sf::Texture* getTexture() const = 0;

	/**
	 * The current visible height for unit is used to visually place units on top of accessible
	 * structures. This can be used for e.g. walls and returns the negative y-axis displacement
	 * which has to be applied to the unit sprite to make it visually stand on top of the structure.
	 * This respects flat mode, so you should not cache this value.
	 * @return The y-axis offset which is always negative to move units "up".
	 */
	virtual float getCurrentVisualHeightForUnits() const = 0;

protected:
	void updateNeighborTextures();

	Coordinates position_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
