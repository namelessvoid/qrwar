#ifndef QRW_SQUARE_HPP
#define QRW_SQUARE_HPP

#include "engine/coordinates.hpp"
#include "engine/terrain.hpp"
#include "engine/unit.hpp"

namespace qrw
{

class Square
{
public:
	Square(int x, int y);
	~Square();

	void setTerrain(Terrain::Ptr terrain);
	Terrain::Ptr getTerrain();

	void setUnit(Unit::Ptr unit);
	Unit::Ptr getUnit();

	int getDistance(Square* suqare);

	const Coordinates& getCoordinates() const;
	int getXPosition();
	int getYPosition();

	bool isAccessible();

private:
	Terrain::Ptr _terrain;
	Unit::Ptr _unit;
	Coordinates _coordinates;
};

} // namespace QRW_SQUARE_HPP

#endif
