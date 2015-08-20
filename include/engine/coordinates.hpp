#ifndef QRW_COORDINATES_HPP
#define QRW_COORDINATES_HPP

namespace qrw
{
	class Coordinates
	{
		public:
			Coordinates(int x = 0, int y = 0);

			int getX() const;
			int getY() const;

			bool operator==(const Coordinates& rhs) const;
			bool operator!=(const Coordinates& rhs) const;

			Coordinates operator+(const Coordinates& rhs) const;
			Coordinates operator-(const Coordinates& rhs) const;

			struct PtrCompLess
			{
				bool operator()(const Coordinates* lhs, const Coordinates* rhs) const;
			};

		private:
			int _x;
			int _y;
	};
}

#endif
