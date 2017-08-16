#ifndef QRW_EVENTHANDLER_HPP
#define QRW_EVENTHANDLER_HPP

namespace qrw
{

class Event;

class EventHandler
{
	virtual bool handleEvent(const Event& event) = 0;
};

}

#endif // QRW_EVENTHANDLER_HPP
