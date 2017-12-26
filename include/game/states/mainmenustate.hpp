#ifndef QRW_MAINMENUSTATE_H
#define QRW_MAINMENUSTATE_H

#include "gamestates/gamestate.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <gui/ng/window.hpp>

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
class RectangleShape;
}

namespace qrw
{

class MainMenuState : public GameState
{
public:
	MainMenuState(sf::RenderWindow* renderWindow);

	void init(GameState *previousState);

	EGameStateId update();

	void draw();

private:
	inline void slotQuitClicked() { nextState_ = EGSID_QUIT; }
	inline void slotNewGameClicked() { nextState_ = EGSID_SKIRMISH_PREPARATION_STATE; }
	inline void slotMapEditorClicked() { nextState_ = EGSID_MAP_EDITOR_STATE; }

	EGameStateId nextState_;

	sf::RectangleShape background_;
};

} // namespace qrw

#endif // QRW_MAINMENUSTATE_H
