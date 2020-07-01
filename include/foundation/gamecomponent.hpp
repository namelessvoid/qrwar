#ifndef QRW_GAMECOMPONENT_HPP
#define QRW_GAMECOMPONENT_HPP

namespace qrw
{

class GameObject;

class GameComponent
{
public:
	explicit GameComponent(GameObject& owner);

	virtual ~GameComponent() = default;

	virtual void onDestroy() {}

	inline GameObject* getOwner() const { return owner_; }

private:
	GameObject* owner_;
};

} // namespace qrw

#endif // QRW_GAMECOMPONENT_HPP
