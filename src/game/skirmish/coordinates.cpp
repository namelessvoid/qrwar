#include "game/skirmish/coordinates.hpp"

#include <cmath>

namespace qrw
{
SID Coordinates::typeName("qrw::Coordinates");

	Coordinates::Coordinates()
	 : Coordinates(0, 0)
	{}
	
	Coordinates::Coordinates(int x, int y)
	 :	_x(x),
		_y(y)
	{}

	int Coordinates::getX() const
	{
		return _x;
	}

	int Coordinates::getY() const
	{
		return _y;
	}

	bool Coordinates::operator==(const Coordinates& rhs) const
	{
		return getX() == rhs.getX() && getY() == rhs.getY();
	}

	bool Coordinates::operator!=(const Coordinates& rhs) const
	{
		return !(*this == rhs);
	}

	bool Coordinates::operator<(const Coordinates& rhs) const
	{
		if(getX() != rhs.getX())
			return getX() < rhs.getX();
		return getY() < rhs.getY();
	}

	bool Coordinates::operator>(const Coordinates& rhs) const
	{
		return rhs < *this;
	}

	Coordinates Coordinates::operator+(const Coordinates& rhs) const
	{
		return Coordinates(getX() + rhs.getX(), getY() + rhs.getY());
	}

	Coordinates Coordinates::operator-(const Coordinates& rhs) const
	{
		return Coordinates(getX() - rhs.getX(), getY() - rhs.getY());
	}

	int Coordinates::distanceTo(const Coordinates& b) const
	{
		int dx = std::abs(getX()) - std::abs(b.getX());
		int dy = std::abs(getY()) - std::abs(b.getY());
		return ceilf(sqrt(dx * dx + dy * dy));
	}
}
