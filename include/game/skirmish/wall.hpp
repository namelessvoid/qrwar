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

	Wall();

	void computeTexture() override;

private:
	bool isConnectedTo(const Coordinates& direction, const Board& board) const;
};

} // namespace qrw

#endif //QRW_WALL_HPP
