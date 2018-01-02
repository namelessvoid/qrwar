#ifndef QRW_SFEVENTSOURCE_HPP
#define QRW_SFEVENTSOURCE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "eventsystem/systemeventsource.hpp"

namespace qrw
{

class SfEventSource : public SystemEventSource
{
public:
    SfEventSource(sf::RenderWindow &window);

	virtual const qrw::IEvent* pollEvent() override;

private:
    sf::RenderWindow& m_window;
};

}

#endif // QRW_SFEVENTSOURCE_HPP
