#ifndef NAMELESSGUI_CROPPINGVIEWFACTORY_HPP
#define NAMELESSGUI_CROPPINGVIEWFACTORY_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace namelessgui {

class CroppingViewFactory
{
public:
    CroppingViewFactory();

    ~CroppingViewFactory();

    sf::View createView(const sf::RenderTarget& renderTarget,
                        const sf::Vector2f& position,
                        const sf::Vector2f& size) const;

private:
    CroppingViewFactory(const CroppingViewFactory& rhs) = delete;

    CroppingViewFactory& operator=(const CroppingViewFactory& rhs) = delete;
};


} // namespace namelessgui

#endif // NAMELESSGUI_CROPPINGVIEWFACTORY_HPP
