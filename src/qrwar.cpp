#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"
#include "config/tilesetprocessor.hpp"

#include "gui/texturemanager.hpp"

#include "core/mouse.hpp"

#include "rendering/rendersystem.hpp"
#include "eventsystem/eventsystem.hpp"
#include "eventsystem/sfeventsource.hpp"
#include "animation/animationsystem.hpp"
#include "physics/physicsengine.hpp"

#include "meta/metamanager.hpp"
#include "game/skirmish/meta/boardmetaclass.hpp"
#include "game/skirmish/meta/terrainmetaclass.hpp"
#include "game/skirmish/meta/wallmetaclass.hpp"
#include "game/skirmish/meta/stairsmetaclass.hpp"
#include "game/skirmish/meta/deploymentzonemetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

#include "game/states/introstate.hpp"
#include "game/states/mainmenustate.hpp"
#include "game/states/mapeditorstate.hpp"
#include "game/states/skirmishpreparationstate.hpp"
#include "game/states/deploystate.hpp"
#include "game/states/skirmishstate.hpp"
#include "game/skirmish/gui/skirmishguifactory.hpp"

#include "game/path.hpp"

#include "game/skirmish/structure.hpp"
#include "game/deploymentzone.hpp"
#include "engine/terrain.hpp"

namespace qrw
{

// Globals within the engine
RenderSystem g_renderSystem;
Scene g_scene;
EventSystem g_eventSystem;
AnimationSystem g_animationSystem;
MetaManager g_metaManager;
PhysicsEngine g_physicsEngine;

// Globals within this file
MapManager mapManager(g_metaManager);

QRWar::QRWar()
{
	// Init
	registerMetaTypes();
	g_renderSystem.startUp(_renderWindow);
	preloadResources();
	g_scene.setRenderTarget(&_renderWindow);
	g_eventSystem.startUp(new SfEventSource(_renderWindow));
	Mouse::setWindow(_renderWindow);
	mapManager.ensureUserMapDir();

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
		float elapsedTimeInSeconds = timer.restart().asSeconds();

		_renderWindow.clear(sf::Color::Black);

		g_eventSystem.update(elapsedTimeInSeconds);

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

		g_scene.update(elapsedTimeInSeconds);
		g_animationSystem.update(elapsedTimeInSeconds);
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
	g_metaManager.registerMetaClass<BoardMetaClass>(Board::typeName);
	g_metaManager.registerMetaClass<TerrainMetaClass>(Terrain::typeName);
	g_metaManager.registerMetaClass<WallMetaClass>(Wall::typeName);
	g_metaManager.registerMetaClass<StairsMetaClass>(Stairs::typeName);
	g_metaManager.registerMetaClass<DeploymentZoneMetaClass>(DeploymentZone::typeName);
	g_metaManager.registerMetaClass<CoordinateMetaClass>(Coordinates::typeName);
}

GameState* QRWar::createGameState(EGameStateId id)
{
	SkirmishGuiFactory guiFactory(mapManager);

	switch(id)
	{
	case EGSID_INTRO_STATE: return new IntroState(&_renderWindow);
	case EGSID_MAIN_MENU_STATE: return new MainMenuState(&_renderWindow);
	case EGSID_MAP_EDITOR_STATE: return new MapEditorState(&_renderWindow, mapManager, guiFactory);
	case EGSID_SKIRMISH_PREPARATION_STATE: return new SkirmishPreparationState(&_renderWindow, mapManager, guiFactory);
	case EGSID_DEPLOY_STATE: return new DeployState(&_renderWindow, mapManager);
	case EGSID_SKIRMISH_STATE: return new SkirmishState(&_renderWindow);
	default: return nullptr;
	}
}

} // namespace qrw
