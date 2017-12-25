#ifndef QRW_PATHFINDING_PATH_HPP
#define QRW_PATHFINDING_PATH_HPP

#include <vector>

#include "engine/coordinates.hpp"

namespace qrw
{

namespace pathfinding
{

class Path
{
	public:
		typedef std::vector<Coordinates>::iterator iterator;
		typedef std::vector<Coordinates>::const_iterator const_iterator;

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		const Coordinates& getStep(int n) const;

		void prependStep(const qrw::Coordinates& position);
		void appendStep(const qrw::Coordinates& position);

		int getLength() const;
		int getMovementCosts() const;

		const Coordinates& getTarget() const;

	private:
		std::vector<qrw::Coordinates> steps_;
};

} // namespace pathfinding

} // namespace qrw

#endif // QRW_PATHFINDING_PATH_HPP
