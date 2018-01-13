#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "config/settings.hpp"
#include "config/tilesetprocessor.hpp"

#include "gui/texturemanager.hpp"

#include "rendering/rendersystem.hpp"
#include "eventsystem/eventsystem.hpp"
#include "eventsystem/sfeventsource.hpp"
#include "animation/animationsystem.hpp"

#include "meta/metamanager.hpp"
#include "game/meta/boardmetaclass.hpp"
#include "game/meta/terrainmetaclass.hpp"

#include "game/states/introstate.hpp"
#include "game/states/mainmenustate.hpp"
#include "game/states/mapeditorstate.hpp"
#include "game/states/skirmishpreparationstate.hpp"
#include "game/states/deploystate.hpp"
#include "game/states/skirmishstate.hpp"

#include "game/path.hpp"

#include "engine/terrain.hpp"

namespace qrw
{

RenderSystem g_renderSystem;
Scene g_scene;
EventSystem g_eventSystem;
AnimationSystem g_animationSystem;

QRWar::QRWar()
{
	// Init
	registerMetaTypes();
	g_renderSystem.startUp(_renderWindow);
	preloadResources();
	g_scene.setRenderTarget(&_renderWindow);
	g_eventSystem.startUp(new SfEventSource(_renderWindow));

	// Set and initialize start state
	_currentState = createGameState(EGSID_INTRO_STATE);
	_currentState->init(nullptr);
}

QRWar::~QRWar()
{
	g_eventSystem.shutDown();
	g_renderSystem.shutDown();
}

void QRWar::run()
{
	sf::Clock timer;

	bool quit = false;
	EGameStateId nextStateId;

	while(!quit)
	{
		sf::Time elapsedTime = timer.restart();

		_renderWindow.clear(sf::Color::Black);

		g_eventSystem.processEvents();

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
			g_renderSystem.renderAll();
			// Todo: Remove _currentState->draw() which only renders gui
			sf::View view = _renderWindow.getView();
			guiCamera_.applyTo(_renderWindow);
			_currentState->draw();
			_renderWindow.setView(view);

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

		g_scene.update();
		g_animationSystem.update(elapsedTime.asSeconds());
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

void QRWar::registerMetaTypes()
{
	MetaManager::registerMetaClass<BoardMetaClass>(Board::typeName);
	MetaManager::registerMetaClass<TerrainMetaClass>(Terrain::typeName);
}

GameState* QRWar::createGameState(EGameStateId id)
{
	switch(id)
	{
	case EGSID_INTRO_STATE: return new IntroState(&_renderWindow);
	case EGSID_MAIN_MENU_STATE: return new MainMenuState(&_renderWindow);
	case EGSID_MAP_EDITOR_STATE: return new MapEditorState(&_renderWindow);
	case EGSID_SKIRMISH_PREPARATION_STATE: return new SkirmishPreparationState(&_renderWindow);
	case EGSID_DEPLOY_STATE: return new DeployState(&_renderWindow);
	case EGSID_SKIRMISH_STATE: return new SkirmishState(&_renderWindow);
	default: return nullptr;
	}
}

} // namespace qrw
