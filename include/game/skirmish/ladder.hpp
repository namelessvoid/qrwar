#ifndef QRW_LADDER_HPP
#define QRW_LADDER_HPP

#include "stairs.hpp"

namespace qrw
{

class Ladder : public WallAccessStructureBase
{
public:
	const SID& getTypeName() const override;

	Ladder();

	const sf::Texture* getTexture() const override;

	void setFace(const Coordinates& face) override;

	void setPosition(const Coordinates& position) override;

	float getCurrentVisualHeightForUnits() const override;

private:
	SpriteComponent* spriteComponent_;
};

} // namespace qrw

#endif // QRW_LADDER_HPP
