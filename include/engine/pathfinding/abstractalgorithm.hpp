#ifndef QRW_ABSTRACTALGORITHM_HPP
#define QRW_ABSTRACTALGORITHM_HPP

namespace qrw
{
	class Board;
	class Path;

	class AbstractAlgorithm
	{
		virtual void setBoard(Board* board) = 0;
		virtual Path* getPath(int startx, int starty, int endx, int endy) = 0;
	};
}

#endif
