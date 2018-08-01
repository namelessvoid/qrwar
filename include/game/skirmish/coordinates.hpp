#ifndef QRW_COORDINATES_HPP
#define QRW_COORDINATES_HPP

#include "core/sid.hpp"

#include "meta/reflectable.hpp"

namespace qrw
{
	class Coordinates : public Reflectable
	{
		public:
			friend class CoordinateMetaClass;
			static SID typeName;

			Coordinates();

			Coordinates(int x, int y);

			Coordinates(const Coordinates& rhs)
			{
				_x = rhs._x;
				_y = rhs._y;
			}

			Coordinates& operator=(const Coordinates& rhs)
			{
				_x = rhs._x;
				_y = rhs._y;
				return *this;
			}

			int getX() const;
			int getY() const;

			bool operator==(const Coordinates& rhs) const;
			bool operator!=(const Coordinates& rhs) const;
			bool operator<(const Coordinates& rhs) const;
			bool operator>(const Coordinates& rhs) const;

			Coordinates operator+(const Coordinates& rhs) const;
			Coordinates operator-(const Coordinates& rhs) const;

			int distanceTo(const Coordinates& b) const;

		private:
			int _x;
			int _y;
	};
}

#endif
