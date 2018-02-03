#include "gui/ng/croppingviewfactory.hpp"

namespace namelessgui
{

CroppingViewFactory::CroppingViewFactory()
{
}

CroppingViewFactory::~CroppingViewFactory()
{
}

sf::View CroppingViewFactory::createView(const sf::RenderTarget& renderTarget,
										 const sf::Vector2f& position,
										 const sf::Vector2f& size) const
{
	sf::View view({position.x, position.y, size.x, size.y});

	sf::FloatRect viewPort({
										position.x / renderTarget.getSize().x,
										position.y / renderTarget.getSize().y,
										size.x / renderTarget.getSize().x,
										size.y / renderTarget.getSize().y
									});

	view.setViewport(viewPort);

	return view;
}

} // namespace namelessgui
