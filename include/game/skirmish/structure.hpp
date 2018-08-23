#ifndef QRW_STRUCTURE_HPP
#define QRW_STRUCTURE_HPP

#include "game/skirmish/coordinates.hpp"
#include "foundation/gameobject.hpp"

namespace qrw
{
class SpriteComponent;

class Structure : public GameObject
{
friend class StructureMetaClass;

public:
	enum class Type { WALL, STAIRS };

	static SID typeName;

	Structure();

	void onAddToScene() override;
	void initialize() override;
	void onDestroy() override;

	void setPosition(const Coordinates& position);
	const Coordinates& getPosition() const { return position_; }

	void setType(Type type) { type_ = type; }

private:
	void computeTexture();
	void updateNeighborTextures();

	SpriteComponent* spriteComponent_;
	Coordinates position_;

	Type type_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
