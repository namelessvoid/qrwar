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

	void set(const pathfinding::Path* path);

	int getMovementCosts() const;

	const Coordinates& getTarget() const;

private:
	Path(const Path& rhs) = delete;

	Path& operator=(const Path& rhs) = delete;

	const pathfinding::Path* path_;

	PathRenderComponent* pathRenderComponent_;
};


} // namespace qrw

#endif // QRW_PATH_HPP
