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
	 * Initialize the GameState.
	 *
	 * The previous GameState is passed as argument so it is possible
	 * to pass parameters from one GameState to another.
	 *
	 * @param previousState Optional pointer to a previous GameState.
	 */
	virtual void init(GameState* previousState = nullptr) = 0;

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

	/**
	 * Handle an SFML event.
	 *
	 * @param event The SFML event to handle.
	 */
	virtual void handleEvent(sf::Event& event) = 0;

	/**
	 * Get the ID of the GameState.
	 *
	 * @return One of the EGameStateIds.
	 */
	EGameStateId getId();

protected:
	sf::RenderWindow* _renderWindow;

private:
	EGameStateId _id;
};

} // namespace qrw

#endif // QRW_GAMESTATE_HPP
