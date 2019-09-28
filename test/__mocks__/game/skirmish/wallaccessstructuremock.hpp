#ifndef QRW_TEST_WALLACCESSSTRUCTUREMOCK_HPP
#define QRW_TEST_WALLACCESSSTRUCTUREMOCK_HPP

#include "game/skirmish/wallaccessstructurebase.hpp"

class WallAccessStructureMock : public qrw::WallAccessStructureBase
{
public:
	const sf::Texture* getTexture() const override
	{
		throw "Not implemented";
	}

	void setFlatMode(bool isFlatMode) override {
		throw "Not implemented";
	}

public:
	const qrw::SID& getTypeName() const override
	{
		throw "Not implemented";
	}
};

#endif //QRW_TEST_WALLACCESSSTRUCTUREMOCK_HPP
