#ifndef QRW_GAMESTATE_HPP
#define QRW_GAMESTATE_HPP

namespace qrw
{

class GameState
{
public:
	GameState(sf::RenderWindow* renderWindow);

	virtual ~GameState();

	virtual void update() = 0;
	virtual void draw()	= 0;

private:
	sf::RenderWindow* _renderWindow;
};

} // namespace qrw

#endif // QRW_GAMESTATE_HPP
