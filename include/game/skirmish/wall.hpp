#ifndef QRW_WALL_HPP
#define QRW_WALL_HPP

#include "structure.hpp"
#include "flatmodeawaremixin.hpp"

namespace qrw
{
class Board;

class Wall : public Structure, public FlatModeAwareMixin
{
public:
	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	const sf::Texture* getTexture() const override;

	Wall();

	void computeTexture() override {}

	void setPosition(const Coordinates& position) override;

	// From FlatModeAwareMixin interface
	void flatModeChanged() override;

	float getCurrentVisualHeightForUnits() const override;

private:
	bool isConnectedTo(const Coordinates& direction, const Board& board) const;

	void updateSprites();

	SpriteComponent* southWallSprite_;
	SpriteComponent* eastWallSprite_;
	SpriteComponent* topFloorSprite_;
};

} // namespace qrw

#endif //QRW_WALL_HPP
