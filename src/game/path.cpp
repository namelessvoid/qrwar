#include "game/path.hpp"

#include <limits>

#include "engine/pathfinding/path.hpp"

#include "game/pathrendercomponent.hpp"
#include "gui/scene.hpp"

namespace qrw
{

Path::Path()
	: path_(nullptr)
{
	pathRenderComponent_ = new PathRenderComponent();
	addComponent(pathRenderComponent_);
}

Path::~Path()
{
	if(path_)
		delete path_;
}

void Path::setStartAndEnd(const Coordinates& start, const Coordinates &end)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	pathfinding::Path* path = board->findPath(start, end);
	setPath(path);
}

void Path::reset()
{
	setPath(nullptr);
}

void Path::setPath(const pathfinding::Path* path)
{
	if(path_)
		delete path_;
	path_ = path;
	pathRenderComponent_->setPath(path);
}

int Path::getMovementCosts() const
{
	if(!path_)
		return std::numeric_limits<int>::max();
	return path_->getMovementCosts();
}

const Coordinates& Path::last() const
{
	assert(path_ != nullptr);
	return path_->getTarget();
}

} // namespace qrw
