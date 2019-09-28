#ifndef QRW_WALL_HPP
#define QRW_WALL_HPP

#include "structure.hpp"

namespace qrw
{
class Board;

class Wall : public Structure
{
public:
	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	void update(float elapsedTimeInSeconds) override;

	const sf::Texture* getTexture() const override;

	Wall();

	void computeTexture() override {}

	void setPosition(const Coordinates& position) override;

	void setFlatMode(bool isFlatMode);

private:
	bool isConnectedTo(const Coordinates& direction, const Board& board) const;
	bool blocksVisibilityOn(const Coordinates& position, const Board& board);

	bool isFlatMode_;

	SpriteComponent* southWallSprite_;
	SpriteComponent* eastWallSprite_;
	SpriteComponent* topFloorSprite_;
};

} // namespace qrw

#endif //QRW_WALL_HPP
