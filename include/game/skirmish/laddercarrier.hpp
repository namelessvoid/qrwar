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

	bool handleEvent(const IEvent& event) override;

private:
	void updateTexture();

	class DeployLadderAbility* deployLadderAbility_;
};

} // namespace qrw

#endif //QRW_LADDERCARRIER_HPP
