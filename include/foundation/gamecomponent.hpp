#ifndef QRW_GAMECOMPONENT_HPP
#define QRW_GAMECOMPONENT_HPP

namespace qrw
{

class GameComponent
{
public:
	virtual ~GameComponent() {}

	virtual void onDestroy() {}
};

} // namespace qrw

#endif // QRW_GAMECOMPONENT_HPP
