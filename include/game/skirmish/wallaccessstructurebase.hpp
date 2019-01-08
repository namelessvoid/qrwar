#ifndef QRW_IMAKEWALLACCESSIBLE_HPP
#define QRW_IMAKEWALLACCESSIBLE_HPP

#include "structure.hpp"
#include "directions.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

/**
 * Base class for structures which grant access to walls (e.g. stairs, ladders).
 */
class WallAccessStructureBase : public Structure
{
public:
	friend class StairsMetaClass;

	WallAccessStructureBase();

	const Coordinates& getFace() const { return face_; }

	void rotate();

	void setFace(const Coordinates& face);

private:
	Coordinates face_;
};

} // namespace qrw

#endif //QRW_IMAKEWALLACCESSIBLE_HPP
