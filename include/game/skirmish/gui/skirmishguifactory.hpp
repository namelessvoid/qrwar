#ifndef QRW_SKIRMISHGUIFACTORY_HPP
#define QRW_SKIRMISHGUIFACTORY_HPP

#include "mapeditortoolbar.hpp"
#include "skirmishpreparationgui.hpp"
#include "mapselectionwindow.hpp"

#include "game/skirmish/mapmanager.hpp"

namespace qrw
{

class SkirmishGuiFactory
{
public:
	explicit SkirmishGuiFactory(MapManager& mapManager)
		: mapManager_(mapManager)
	{}

	virtual MapEditorToolBar* createMapEditorToolBar(unsigned int initialBoardWidth, unsigned initialBoardHeight) const
	{
		return new MapEditorToolBar(initialBoardWidth, initialBoardHeight);
	}

	virtual SkirmishPreparationGui* createSkirmishPreparationGui() const
	{
		return new SkirmishPreparationGui(*this);
	}

	virtual MapSelectionWindow* createMapSelectionWindow() const
	{
		return new MapSelectionWindow(mapManager_);
	}

private:
	MapManager& mapManager_;
};

} // namespace qrw

#endif //QRW_SKIRMISHGUIFACTORY_HPP
