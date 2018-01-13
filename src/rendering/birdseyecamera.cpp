#include "rendering/birdseyecamera.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace qrw
{

BirdsEyeCamera::BirdsEyeCamera()
	: center_(0, 0)
{
}

BirdsEyeCamera::~BirdsEyeCamera()
{
}

void BirdsEyeCamera::applyTo(sf::RenderTarget& renderTarget)
{
	sf::View view = renderTarget.getView();
	view.setCenter(center_);
	renderTarget.setView(view);
}

bool BirdsEyeCamera::handleEvent(const IEvent& event)
{
	return false;
}

} // namespace qrw
