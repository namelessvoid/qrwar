#ifndef QRW_DEPLOYMENTZONE_HPP
#define QRW_DEPLOYMENTZONE_HPP

#include <set>

#include <SFML/Graphics/Color.hpp>

#include "core/sid.hpp"
#include "foundation/gameobject.hpp"
#include "rendering/renderable.hpp"

#include "engine/coordinates.hpp"

namespace qrw {

class DeploymentZone : public GameObject, public Renderable
{
friend class DeploymentZoneMetaClass;

public:
	DeploymentZone();

	virtual ~DeploymentZone();

	virtual void render(sf::RenderTarget& renderTarget) override;

	virtual void setPosition(const sf::Vector2f& position) override;

	virtual const sf::Vector2f& getPosition() const override;

	void setColor(const sf::Color& color);

	void addSquare(const Coordinates& coordinate);
	void removeSquare(const Coordinates& coordinate);

	bool containsSquare(const Coordinates& coordinate);

	static SID typeName;

private:
	sf::Vector2f position_;

	std::set<Coordinates> zone_;

	sf::Color color_;

	DeploymentZone(const DeploymentZone& rhs) = delete;

	DeploymentZone& operator=(const DeploymentZone& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONE_HPP
