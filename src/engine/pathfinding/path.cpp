#include "engine/pathfinding/path.hpp"

#include "engine/coordinates.hpp"

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

	const Coordinates &Path::getStep(int n) const
	{
		return steps.at(n);
	}

	void Path::prependStep(const Coordinates& position)
	{
		steps.insert(steps.begin(), position);
	}

	void Path::appendStep(const Coordinates& position)
	{
		steps.push_back(position);
	};

	int Path::getLength()
	{
		return steps.size();
	}

	int Path::getMovementCosts()
	{
		return getLength() - 1;
	}

	const Coordinates& Path::getTarget() const
	{
		return steps.back();
	}
}
