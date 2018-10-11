#ifndef QRW_LADDERCARRIER_HPP
#define QRW_LADDERCARRIER_HPP

#include "unit.hpp"

namespace qrw
{

class LadderCarrier : public Unit
{
public:
	LadderCarrier();

	void onAddToScene() override;
};

} // namespace qrw

#endif //QRW_LADDERCARRIER_HPP
