#include "engine/pathfinding/path.hpp"

#include "game/skirmish/coordinates.hpp"

namespace qrw
{
namespace pathfinding
{
	Path::iterator Path::begin()
	{
		return steps_.begin();
	};

	Path::const_iterator Path::begin() const
	{
		return steps_.begin();
	};

	Path::iterator Path::end()
	{
		return steps_.end();
	};

	Path::const_iterator Path::end() const
	{
		return steps_.end();
	};

	const Coordinates& Path::getStep(int n) const
	{
		return steps_.at(n);
	}

	void Path::prependStep(const qrw::Coordinates& position)
	{
		steps_.insert(steps_.begin(), position);
	}

	void Path::appendStep(const qrw::Coordinates& position)
	{
		steps_.push_back(position);
	};

	int Path::getLength() const
	{
		return steps_.size();
	}

	int Path::getMovementCosts() const
	{
		return getLength() - 1;
	}

	const Coordinates& Path::getTarget() const
	{
		return steps_.back();
	}
} // namespace pathfinding

} // namespace qrw
