#include "rendering/guicamera.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace qrw
{

GuiCamera::GuiCamera()
{
}

GuiCamera::~GuiCamera()
{
}

void GuiCamera::applyTo(sf::RenderTarget& renderTarget)
{
	sf::View view({
					  0,
					  0,
					  static_cast<float>(renderTarget.getSize().x),
					  static_cast<float>(renderTarget.getSize().y)
				  });
	renderTarget.setView(view);
}

} // namespace qrw
