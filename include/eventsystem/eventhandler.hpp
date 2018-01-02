#ifndef QRW_EVENTHANDLER_HPP
#define QRW_EVENTHANDLER_HPP

namespace qrw
{

class IEvent;

class EventHandler
{
public:
	EventHandler();

	virtual ~EventHandler();

	virtual bool handleEvent(const IEvent& event) = 0;
};

}

#endif // QRW_EVENTHANDLER_HPP
