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

protected:
	void updateNeighborTextures();

	Coordinates position_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
