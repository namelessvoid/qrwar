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
	static SID typeName;

	Structure();

	void onAddToScene() override;

	void setPosition(const Coordinates& position);
	const Coordinates& getPosition() const { return position_; }

	void setType(unsigned int type) { type_ = type; }

private:
	SpriteComponent* spriteComponent_;
	Coordinates position_;

	unsigned int type_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
