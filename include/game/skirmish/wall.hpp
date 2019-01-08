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

private:
	bool isConnectedTo(const Coordinates& direction, const Board& board) const;
	bool blocksVisibilityOn(const Coordinates& position, const Board& board);

	SpriteComponent* southWallSprite_;
	SpriteComponent* eastWallSprite_;
	SpriteComponent* topFloorSprite_;
};

} // namespace qrw

#endif //QRW_WALL_HPP
