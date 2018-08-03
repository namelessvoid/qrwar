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
	Structure();

	void setPosition(const Coordinates& position);
	const Coordinates& getPosition() const { return position_; }

private:
	SpriteComponent* spriteComponent_;
	Coordinates position_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
