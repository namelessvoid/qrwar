#ifndef QRW_PATH_HPP
#define QRW_PATH_HPP

#include "engine/pathfinding/path.hpp"
#include "foundation/gameobject.hpp"

namespace qrw {

class Coordinates;
class PathRenderComponent;

class Path : public GameObject
{
public:
	const SID& getTypeName() const override	{ throw "Not implemented"; }

	Path();

	~Path() override;

	Path(const Path& rhs) = delete;
	Path& operator=(const Path& rhs) = delete;

	void setStartAndEnd(const Coordinates& start, const Coordinates& end);
	void reset();

	int getMovementCosts() const;

	const Coordinates& last() const;

	int getLength() const { return path_->getLength(); }
	const Coordinates& getStep(int n) const { return path_->getStep(n); }

	pathfinding::Path::const_iterator begin() const { return path_->begin(); };
	pathfinding::Path::const_iterator end() const { return path_->end(); };

private:

	void setPath(const pathfinding::Path* path);

	const pathfinding::Path* path_;

	PathRenderComponent* pathRenderComponent_;
};


} // namespace qrw

#endif // QRW_PATH_HPP
