#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include <vector>

namespace qrw
{
	class Square;
	class Coordinates;

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

			void prependStep(const Coordinates& position);
			void appendStep(const Coordinates& position);

			int getLength();
			int getMovementCosts();

			const Coordinates& getTarget() const;

		private:
			std::vector<Coordinates> steps;
	};
}

#endif
