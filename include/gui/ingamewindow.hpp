#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFML/System/Vector2.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>

#include "engine/engine.hpp"

namespace qrw
{
	class IngameWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<IngameWindow> Ptr;
			typedef sfg::SharedPtr<const IngameWindow> PtrConst;

			static Ptr Create(Engine* engine, sf::Vector2f windowsize);

			sf::Vector2f getSize();

			void update();

		protected:
			IngameWindow(Engine* engine);

		private:
			void changeplayerbuttonClicked();

			Engine* engine;
	};
}

#endif