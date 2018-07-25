#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include "foundation/gameobject.hpp"

namespace qrw {
namespace pathfinding {
class Path;
}

class Coordinates;
class PathRenderComponent;

class Path : public GameObject
{
public:
	Path();

	~Path();

	void setStartAndEnd(const Coordinates& start, const Coordinates& end);
	void reset();

	int getMovementCosts() const;

	const Coordinates& last() const;

private:
	Path(const Path& rhs) = delete;

	Path& operator=(const Path& rhs) = delete;

	void setPath(const pathfinding::Path* path);

	const pathfinding::Path* path_;

	PathRenderComponent* pathRenderComponent_;
};


} // namespace qrw

#endif // QRW_PATH_HPP
