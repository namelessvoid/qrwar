#include "engine/pathfinding/path.hpp"
#include "engine/square.hpp"

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

	void Path::appendStep(Square* square)
	{
		steps.push_back(square);
	};

	int Path::getLength()
	{
		return steps.size();
	}
}
