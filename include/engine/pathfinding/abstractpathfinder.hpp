#ifndef QRW_ABSTRACTALGORITHM_HPP
#define QRW_ABSTRACTALGORITHM_HPP

namespace qrw
{
	class Board;
	class Path;
	class Coordinates;

	class AbstractPathfinder
	{
		public:
			virtual ~AbstractPathfinder() {}

			virtual void setBoard(Board* board) = 0;
			virtual Path* findPath(const Coordinates& start, const Coordinates& end) = 0;
	};
}

#endif
