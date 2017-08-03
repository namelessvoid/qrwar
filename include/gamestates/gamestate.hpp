#ifndef QRW_GAMESTATE_HPP
#define QRW_GAMESTATE_HPP

#include <memory>

#include "gui/ng/gui.hpp"

#include "eventsystem/eventhandler.hpp"

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
}

namespace qrw
{

/**
 * Enum containing the identifiers of available game states.
 */
enum EGameStateId
{
	/**
	 * The ID of te IntroState.
	 */
	EGSID_INTRO_STATE,

	/**
	 * The ID of the MainMenuState.
	 */
	EGSID_MAIN_MENU_STATE,

	/**
	 * The ID of the MapEditorState.
	 */
	EGSID_MAP_EDITOR_STATE,

	/**
	 * The ID of the DeployGameState.
	 */
	EGSID_DEPLOY_STATE,

    /**
      * The ID of the SkrimishState.
      */
    EGSID_SKIRMISH_STATE,

	/**
	 * Special "game state" that indicates that the application should quit.
	 */
	EGSID_QUIT,

	/**
	 * Special "game state" that indicates that no game state change
	 * should be performed by the QRWar object.
	 */
	EGSID_NO_CHANGE,

	/**
	 * Holds the number of game states.
	 */
	EGSID_COUNT
};

/**
 * The GameState class represents a state of the game.
 *
 * It is used to encapuslate all data and methods required for a specific
 * state.
 */
class GameState : public EventHandler
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
	virtual void init(GameState* previousState = nullptr);

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
	 *
	 * @return Whether the event propagation should be stopped or not.
	 */
	virtual bool handleEvent(sf::Event& event);

	virtual bool handleEvent(const Event& event) override;

	/**
	 * Get the ID of the GameState.
	 *
	 * @return One of the EGameStateIds.
	 */
	EGameStateId getId();

protected:
	sf::RenderWindow* _renderWindow;

	std::unique_ptr<namelessgui::Gui> _guiUptr;

private:
	EGameStateId _id;
};

} // namespace qrw

#endif // QRW_GAMESTATE_HPP
