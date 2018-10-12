#ifndef QRW_EVENTHANDLER_HPP
#define QRW_EVENTHANDLER_HPP

namespace qrw
{

class IEvent;

class EventHandler
{
public:
	explicit EventHandler(int priority);

	virtual ~EventHandler();

	virtual bool handleEvent(const IEvent& event) = 0;

	inline int getPriority() { return priority_; }

private:
	const int priority_;
};

}

#endif // QRW_EVENTHANDLER_HPP
