#ifndef QRW_SKIRMISHGUIFACTORY_HPP
#define QRW_SKIRMISHGUIFACTORY_HPP

#include "mapeditortoolbar.hpp"
#include "skirmishpreparationgui.hpp"

namespace qrw
{

class SkirmishGuiFactory
{
public:
	virtual MapEditorToolBar* createMapEditorToolBar(unsigned int initialBoardWidth, unsigned initialBoardHeight) const
	{
		return new MapEditorToolBar(initialBoardWidth, initialBoardHeight);
	}

	virtual SkirmishPreparationGui* createSkirmishPreparationGui() const
	{
		return new SkirmishPreparationGui();
	}
};

} // namespace qrw

#endif //QRW_SKIRMISHGUIFACTORY_HPP
