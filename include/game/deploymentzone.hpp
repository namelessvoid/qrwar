#ifndef QRW_DEPLOYMENTZONE_HPP
#define QRW_DEPLOYMENTZONE_HPP

#include <set>

#include <SFML/Graphics/Color.hpp>

#include "foundation/gameobject.hpp"
#include "rendering/renderable.hpp"

#include "engine/coordinates.hpp"

namespace qrw {

class DeploymentZone : public GameObject, public Renderable
{
public:
	DeploymentZone();

	~DeploymentZone();

	virtual void render(sf::RenderTarget& renderTarget) override;

	virtual void setPosition(const sf::Vector2f& position) override;

	virtual const sf::Vector2f& getPosition() const override;

	void setColor(const sf::Color& color);

	void addSquare(const Coordinates& coordinate);

	bool containsSquare(const Coordinates& coordinate);

private:
	sf::Vector2f position_;

	std::set<Coordinates> zone_;

	sf::Color color_;

	DeploymentZone(const DeploymentZone& rhs) = delete;

	DeploymentZone& operator=(const DeploymentZone& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONE_HPP
