#ifndef QRW_DEPLOYMENTZONE_HPP
#define QRW_DEPLOYMENTZONE_HPP

#include <set>
#include <map>

#include "core/sid.hpp"
#include "foundation/gameobject.hpp"
#include "foundation/spritecomponent.hpp"

#include "game/skirmish/coordinates.hpp"

namespace qrw {

class DeploymentZone : public GameObject
{
friend class DeploymentZoneMetaClass;

public:
	const static SID typeName;
	const SID& getTypeName() const override	{ return typeName; }

	DeploymentZone();

//	void render(sf::RenderTarget& renderTarget) override;

	void addSquare(const Coordinates& coordinate);
	void removeSquare(const Coordinates& coordinate);
	bool containsSquare(const Coordinates& coordinate);
	void crop(const Coordinates& size);

	size_t getSize() const { return zone_.size(); }

	void setPlayerId(int playerId);
	int getPlayerId() const { return playerId_; }

	void initialize() override;

private:
	void updateSprites();
	void updateSprite(const Coordinates& coordinates, SpriteComponent* sprite);

	int playerId_;

	std::set<Coordinates> zone_;
	std::map<Coordinates, SpriteComponent*> sprites_;

	sf::Color color_;

	DeploymentZone(const DeploymentZone& rhs) = delete;

	DeploymentZone& operator=(const DeploymentZone& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONE_HPP
