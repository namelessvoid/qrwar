#ifndef QRW_IMAKEWALLACCESSIBLE_HPP
#define QRW_IMAKEWALLACCESSIBLE_HPP

#include "structure.hpp"
#include "directions.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

/**
 * Marker interface (primarily intended for structures). Marks objects
 * as being intende to grant access from ground to a wall, e.g. stairs,
 * and ladders.
 */
class IMakeWallAccessible : public Structure
{
public:
	friend class StairsMetaClass;

	IMakeWallAccessible();

	void computeTexture() override;

	const Coordinates& getFace() const { return face_; }

	void rotate();

	void setFace(const Coordinates& face);

	void setPosition(const Coordinates& position) override;

private:
	Coordinates face_;
};

} // namespace qrw

#endif //QRW_IMAKEWALLACCESSIBLE_HPP
