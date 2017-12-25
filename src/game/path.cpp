#include "game/path.hpp"

#include "engine/pathfinding/path.hpp"

namespace qrw
{

Path::Path()
	: path_(nullptr)
{
}

Path::~Path()
{
	if(path_)
		delete path_;
}

void Path::set(const pathfinding::Path* path)
{
	if(path_)
		delete path_;
	path_ = path;
}

int Path::getMovementCosts() const
{
	assert(path_ != nullptr);
	return path_->getMovementCosts();
}

const Coordinates& Path::getTarget() const
{
	assert(path_ != nullptr);
	return path_->getTarget();
}

} // namespace qrw
