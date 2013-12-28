#ifndef QRW_COORDINATES_HPP
#define QRW_COORDINATES_HPP

namespace qrw
{
	class Coordinates
	{
		public:
			Coordinates(int x = 0, int y = 0);

			void setX(int x);
			int getX() const;

			void setY(int y);
			int getY() const;

			struct PtrCompLess
			{
				bool operator()(const Coordinates* lhs, const Coordinates* rhs) const;
			};

		private:
			int x;
			int y;
	};
}

#endif
