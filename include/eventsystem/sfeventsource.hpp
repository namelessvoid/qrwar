#ifndef QRW_SFEVENTSOURCE_HPP
#define QRW_SFEVENTSOURCE_HPP

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "eventsystem/systemeventsource.hpp"
#include "eventsystem/inputevents.hpp"

namespace qrw
{

class SfEventSource : public SystemEventSource
{
public:
    SfEventSource(sf::RenderWindow &window);

	virtual const qrw::IEvent* pollEvent() override;

private:
    sf::RenderWindow& m_window;

	std::map<sf::Keyboard::Key,KeyboardKey> keyMap_;
};

}

#endif // QRW_SFEVENTSOURCE_HPP
