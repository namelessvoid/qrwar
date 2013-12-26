#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include <vector>

namespace qrw
{
	class Coordinates;

	class Path
	{
		public:
			typedef std::vector<Coordinates*>::iterator iterator;
			typedef std::vector<Coordinates*>::const_iterator const_iterator;

			~Path();

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			void appendStep(Coordinates* coordinates);

			int getLength();

		private:
			std::vector<Coordinates*> steps;
	};
}

#endif
