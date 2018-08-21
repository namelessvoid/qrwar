#ifndef QRW_MAPDTO_HPP
#define QRW_MAPDTO_HPP

#include <utility>
#include <vector>

namespace qrw
{
class Board;
class DeploymentZone;

struct MapDto
{
	MapDto() = default;

	Board* board = nullptr;
	std::vector<DeploymentZone*> deploymentZones;
//	std::set<Terrain*> terrains;
//	std::set<Structure*> structures;
};

}

#endif //QRW_MAPDTO_HPP
