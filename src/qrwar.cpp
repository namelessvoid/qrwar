#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"
#include "config/tilesetprocessor.hpp"

#include "gui/texturemanager.hpp"

#include "rendering/rendersystem.hpp"

#include "eventsystem/eventsystem.hpp"

#include "gamestates/introstate.hpp"
#include "gamestates/mainmenustate.hpp"
#include "gamestates/mapeditorstate.hpp"
#include "gamestates/deploystate.hpp"
#include "gamestates/skirmishstate.hpp"

namespace qrw
{

RenderSystem g_renderSystem;
Scene g_scene;
EventSystem g_eventSystem;

QRWar::QRWar()
{
	// Init
	g_renderSystem.startUp();
	preloadResources();
	g_scene.setRenderTarget(&_renderWindow);

	// Set and initialize start state
	_currentState = createGameState(EGSID_INTRO_STATE);
	_currentState->init(nullptr);
}

QRWar::~QRWar()
{
	g_renderSystem.shutDown();
}

void QRWar::run()
{
	sf::Event event;
	std::shared_ptr<const Event> qrwEvent;

	bool quit = false;
	EGameStateId nextStateId;

	while(!quit)
	{
		_renderWindow.clear(sf::Color::Black);

		while(_renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                quit = true;

			_currentState->handleEvent(event);
        }

		while(g_eventSystem.popEvent(qrwEvent))
			_currentState->handleEvent(*qrwEvent);

		qrwEvent.reset();

		nextStateId = _currentState->update();

		// Quit the application
		if(nextStateId == EGameStateId::EGSID_QUIT)
		{
			quit = true;
			delete _currentState;
			g_scene.reset();
		}
		// If no state change occured: draw the current state
		else if(nextStateId == EGameStateId::EGSID_NO_CHANGE)
		{
			// Todo: Remove _currentState->draw();
			g_renderSystem.renderAll(_renderWindow);
			_currentState->draw();
			_renderWindow.display();
		}
		// Perform a state change
		else
		{
			GameState* previousState = _currentState;
			_currentState = createGameState(nextStateId);
			_currentState->init(previousState);
			delete previousState;
		}
	}
}

void QRWar::preloadResources()
{
	// Start initialization of qrw...
	// Load Settings
	qrw::Settings* settings = qrw::Settings::getInstance();
	settings->loadFromFile();

	TextureManager::getInstance()->loadTexture("mainmenubackground", "./res/img/mainmenubackground.png");

	// Loading tilesets
	qrw::TilesetProcessor tilesetprocessor;
	tilesetprocessor.loadTileset(settings->getEntityTilesetPath());
	tilesetprocessor.loadTileset(settings->getGuiTilesetPath());
}

GameState* QRWar::createGameState(EGameStateId id)
{
	switch(id)
	{
	case EGSID_INTRO_STATE: return new IntroState(&_renderWindow);
	case EGSID_MAIN_MENU_STATE: return new MainMenuState(&_renderWindow);
	case EGSID_MAP_EDITOR_STATE: return new MapEditorState(&_renderWindow);
	case EGSID_DEPLOY_STATE: return new DeployState(&_renderWindow);
	case EGSID_SKIRMISH_STATE: return new SkirmishState(&_renderWindow);
	default: return nullptr;
	}
}

} // namespace qrw
