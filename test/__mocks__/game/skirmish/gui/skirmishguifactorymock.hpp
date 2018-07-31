#ifndef QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP
#define QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP

#include <gmock/gmock.h>

#include "game/skirmish/gui/skirmishguifactory.hpp"

class SkirmishGuiFactoryMock : public qrw::SkirmishGuiFactory
{
public:
	MOCK_CONST_METHOD2(createMapEditorToolBar, qrw::MapEditorToolBar*(unsigned int initialBoardWidth, unsigned int initialBoardHeight));
};

#endif //QRWTEST_SKIRMISHGUIFACTORYMOCK_HPP
