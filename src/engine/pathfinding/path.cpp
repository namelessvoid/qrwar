#include "engine/pathfinding/path.hpp"
#include "engine/square.hpp"

namespace qrw
{
	Path::iterator Path::begin()
	{
		return steps.begin();
	};

	Path::const_iterator Path::begin() const
	{
		return steps.begin();
	};

	Path::iterator Path::end()
	{
		return steps.end();
	};

	Path::const_iterator Path::end() const
	{
		return steps.end();
	};

	Square* Path::getStep(int n) const
	{
		return steps.at(n);
	}

	void Path::prependStep(Square* square)
	{
		steps.insert(steps.begin(), square);
	}

	void Path::appendStep(Square* square)
	{
		steps.push_back(square);
	};

	int Path::getLength()
	{
		return steps.size();
	}

	int Path::getMovementCosts()
	{
		return getLength() - 1;
	}
}
