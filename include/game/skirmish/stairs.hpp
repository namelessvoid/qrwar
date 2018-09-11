#ifndef QRW_STAIRS_HPP
#define QRW_STAIRS_HPP

#include "structure.hpp"

#include "directions.hpp"

namespace qrw
{

class Stairs : public Structure
{
public:
	friend class StairsMetaClass;

	static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	Stairs();

	void computeTexture() override;

	void setPosition(const Coordinates& position) override;

	void rotate();

	const Coordinates& getFace() const { return face_; }

private:
	Coordinates face_;
};

} // namespace qrw

#endif //QRW_STAIRS_HPP
