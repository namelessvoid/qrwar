#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include <vector>

namespace qrw
{
	class Square;

	class Path
	{
		public:
			typedef std::vector<Square*>::iterator iterator;
			typedef std::vector<Square*>::const_iterator const_iterator;

			~Path();

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			void appendStep(Square* square);

			int getLength();

		private:
			std::vector<Square*> steps;
	};
}

#endif
