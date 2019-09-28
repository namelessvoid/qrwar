#ifndef QRW_STAIRS_HPP
#define QRW_STAIRS_HPP

#include "wallaccessstructurebase.hpp"

namespace qrw
{

class Stairs : public WallAccessStructureBase
{
public:
	friend class StairsMetaClass;

	const sf::Texture* getTexture() const override;

	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	Stairs();

	void setFlatMode(bool isFlatMode) override {}

private:
	SpriteComponent* spriteComponent_;
};

} // namespace qrw

#endif //QRW_STAIRS_HPP
