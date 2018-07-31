#ifndef QRW_STRUCTURE_HPP
#define QRW_STRUCTURE_HPP

#include "engine/coordinates.hpp"
#include "foundation/gameobject.hpp"

namespace qrw
{
class SpriteComponent;

class Structure : public GameObject
{
public:
	Structure();

	void setPosition(const Coordinates& position);

private:
	SpriteComponent* spriteComponent_;
	Coordinates position_;
};

} // namespace qrw

#endif //QRW_STRUCTURE_HPP
