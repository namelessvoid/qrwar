#ifndef QRW_PLACEUNITWINDOW_HPP
#define QRW_PLACEUNITWINDOW_HPP

#include <SFGUI/Window.hpp>

#include "engine/engine.hpp"

namespace qrw
{
	class PlaceUnitWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<PlaceUnitWindow> Ptr;
			typedef sfg::SharedPtr<const PlaceUnitWindow> PtrConst;

			static Ptr Create(Engine* engine);

			void update();
			void setPlayerUnits(int p1units[], int p2units[]);

			void placeUnitAtCursor();

		protected:
			PlaceUnitWindow(Engine* engine);

		private:
			int getSelectedPlayerId();
			int getSelectedUnitType();

			void startgamebuttonClicked();
			
			Engine* engine;
			// Arrays of player units
			int p1units[EUT_NUMBEROFUNITTYPES];
			int p2units[EUT_NUMBEROFUNITTYPES];
	};
}
#endif