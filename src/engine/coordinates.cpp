#include "engine/coordinates.hpp"

namespace qrw
{
	Coordinates::Coordinates(int x, int y)
	 :	x(x),
	 	y(y)
	{}

	int Coordinates::getX() const
	{
		return x;
	}

	int Coordinates::getY() const
	{
		return y;
	}

	bool Coordinates::PtrCompLess::operator()(const Coordinates* lhs, const Coordinates* rhs) const
	{
		if(lhs->getX() != rhs->getX())
			return lhs->getX() < rhs->getX();
		return lhs->getY() < rhs->getY();
	}
}
