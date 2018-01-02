#ifndef QRW_SYSTEMEVENTSOURCE_HPP
#define QRW_SYSTEMEVENTSOURCE_HPP

namespace qrw
{

class SystemEventSource
{
public:
    virtual ~SystemEventSource() {}

	virtual const class IEvent* pollEvent() = 0;
};

}

#endif // QRW_SYSTEMEFENTSOURCE_HPP
