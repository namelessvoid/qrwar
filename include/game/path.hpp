#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include "foundation/gameobject.hpp"

#include "engine/pathfinding/path.hpp"

namespace qrw {
//namespace pathfinding {
//class Path;
//}

class Coordinates;

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
};


} // namespace qrw

#endif // QRW_PATH_HPP
