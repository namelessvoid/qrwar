#include "engine/coordinates.hpp"

namespace qrw
{
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

	void Coordinates::setX(int x)
	{
		_x = x;
	}

	void Coordinates::setY(int y)
	{
		_y = y;
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

	Coordinates Coordinates::operator+(const Coordinates& rhs) const
	{
		return Coordinates(getX() + rhs.getX(), getY() + rhs.getY());
	}

	Coordinates Coordinates::operator-(const Coordinates& rhs) const
	{
		return Coordinates(getX() - rhs.getX(), getY() - rhs.getY());
	}

	bool Coordinates::PtrCompLess::operator()(const Coordinates* lhs, const Coordinates* rhs) const
	{
		if(lhs->getX() != rhs->getX())
			return lhs->getX() < rhs->getX();
		return lhs->getY() < rhs->getY();
	}
}
