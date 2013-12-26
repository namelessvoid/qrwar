#include "engine/pathfinding/path.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	Path::~Path()
	{
		for(auto step : steps)
			delete step;

		steps.clear();
	};

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

	void Path::appendStep(Coordinates* coordinates)
	{
		steps.push_back(coordinates);
	};

	int Path::getLength()
	{
		return steps.size();
	}
}
