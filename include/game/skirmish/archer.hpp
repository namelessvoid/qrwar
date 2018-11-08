#ifndef QRW_ARCHER_HPP
#define QRW_ARCHER_HPP

#include "unit.hpp"

namespace qrw
{

class Archer : public Unit
{
public:
	Archer();

	void onAddToScene() override;
};

} // namespace qrw

#endif //QRW_ARCHER_HPP
