#include "engine/coordinates.hpp"

namespace qrw
{
	Coordinates::Coordinates(int x, int y)
	 :	x(x),
	 	y(y)
	{}

	void Coordinates::setX(int x)
	{
		this->x = x;
	}

	int Coordinates::getX() const
	{
		return x;
	}

	void Coordinates::setY(int y)
	{
		this->y = y;
	}

	int Coordinates::getY() const
	{
		return y;
	}
}
