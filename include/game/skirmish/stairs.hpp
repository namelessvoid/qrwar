#ifndef QRW_STAIRS_HPP
#define QRW_STAIRS_HPP

#include "wallaccessstructurebase.hpp"
#include "flatmodeawaremixin.hpp"

namespace qrw
{

class Stairs : public WallAccessStructureBase, public FlatModeAwareMixin
{
public:
	friend class StairsMetaClass;

	const sf::Texture* getTexture() const override;

	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	Stairs();

	void setPosition(const Coordinates& position) override;

	void computeTexture() override;

	void flatModeChanged() override;

private:
	SpriteComponent* spriteComponent_;
};

} // namespace qrw

#endif //QRW_STAIRS_HPP
