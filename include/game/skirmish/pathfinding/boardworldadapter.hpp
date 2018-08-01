#ifndef QRW_BOARDWORLDADAPTER_HPP
#define QRW_BOARDWORLDADAPTER_HPP

#include <array>

#include "engine/pathfinding/iworldadapter.hpp"

#include "game/skirmish/coordinates.hpp"

namespace qrw
{
class Board;

class BoardWorldAdapter : public IWorldAdapter<Coordinates>
{
public:
	explicit BoardWorldAdapter(const Board& board);

	bool isAccessible(const Coordinates& location) const override;

	std::vector<Coordinates> getNeighborLocationsFor(const Coordinates& location) const override;

private:
	const Board& board_;

	static const std::array<const Coordinates,4> directions_;
};

} // namespace qrw

#endif // QRW_BOARDWORLDADAPTER_HPP
