#ifndef QRW_SKIRMISHGUIFACTORY_HPP
#define QRW_SKIRMISHGUIFACTORY_HPP

#include "mapeditortoolbar.hpp"

namespace qrw
{

class SkirmishGuiFactory
{
public:
	virtual MapEditorToolBar* createMapEditorToolBar(unsigned int initialBoardWidth, unsigned initialBoardHeight) const
	{
		return new MapEditorToolBar(initialBoardWidth, initialBoardHeight);
	}
};

}

#endif //QRW_SKIRMISHGUIFACTORY_HPP
