#ifndef QRW_DEPLOYMENTZONE_HPP
#define QRW_DEPLOYMENTZONE_HPP

#include <set>

#include <SFML/Graphics/Color.hpp>

#include "core/sid.hpp"
#include "foundation/gameobject.hpp"
#include "rendering/renderable.hpp"

#include "game/skirmish/coordinates.hpp"

namespace qrw {

class DeploymentZone : public GameObject, public Renderable
{
friend class DeploymentZoneMetaClass;

public:
	DeploymentZone();

	~DeploymentZone() override;

	void render(sf::RenderTarget& renderTarget) override;

	void setPosition(const sf::Vector2f& position) override;
	const sf::Vector2f& getPosition() const override;

	void addSquare(const Coordinates& coordinate);
	void removeSquare(const Coordinates& coordinate);
	bool containsSquare(const Coordinates& coordinate);
	void crop(const Coordinates& size);

	size_t getSize() const { return zone_.size(); }

	void setPlayerId(int playerId);
	int getPlayerId() const { return playerId_; }

	static SID typeName;

private:
	int playerId_;

	sf::Vector2f position_;

	std::set<Coordinates> zone_;

	sf::Color color_;

	DeploymentZone(const DeploymentZone& rhs) = delete;

	DeploymentZone& operator=(const DeploymentZone& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONE_HPP
