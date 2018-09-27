#ifndef QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP
#define QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP

#include <gmock/gmock.h>

#include "game/skirmish/gui/skirmishguifactory.hpp"

#include "__mocks__/game/skirmish/mapmanagermock.hpp"

class SkirmishGuiFactoryMock : public qrw::SkirmishGuiFactory
{
public:
	SkirmishGuiFactoryMock() : qrw::SkirmishGuiFactory(mapManagerMock) {}

	MOCK_CONST_METHOD2(createMapEditorToolBar, qrw::MapEditorToolBar*(unsigned int initialBoardWidth, unsigned int initialBoardHeight));

private:
	MapManagerMock mapManagerMock;
};

#endif //QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP
