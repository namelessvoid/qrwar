#ifndef QRW_GAMESTATE_HPP
#define QRW_GAMESTATE_HPP

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
}

namespace qrw
{

enum EGameStateId
{
	EGSID_INTRO,
	EGSID_QUIT,
	EGSID_NO_CHANGE,
	EGSID_COUNT
};

class GameState
{
public:
	/**
	 * GameState constructor.
	 *
	 * @param renderWindow The sf::RenderWindow in which the game takes place.
	 */
	GameState(sf::RenderWindow* renderWindow, EGameStateId id);

	/**
	 * Destroy a GameState.
	 */
	virtual ~GameState();

	/**
	 * Update the GameState.
	 *
	 * @return The ID of the next GameState, EGSID_NO_CHANGE, if the state did not chnage
	 *         or EGSID_QUIT if the GameState wants the application to quit.
	 */
	virtual EGameStateId update() = 0;

	/**
	 * Render the GameState to the render window.
	 */
	virtual void draw()	= 0;

	virtual void handleEvent(sf::Event& event) = 0;

	/**
	 * Get the ID of the GameState.
	 *
	 * @return One of the EGameStateIds.
	 */
	EGameStateId getId();

private:
	sf::RenderWindow* _renderWindow;

	EGameStateId _id;
};

} // namespace qrw

#endif // QRW_GAMESTATE_HPP
