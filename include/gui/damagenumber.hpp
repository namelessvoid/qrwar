#ifndef QRW_DAMAGENUMER_HPP
#define QRW_DAMAGENUMER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Time.hpp>

#include "gui/animation.hpp"

namespace qrw
{
	class DamageNumber : public Animation
	{
		public:
			DamageNumber(int damagedone, sf::Vector2f position);
			~DamageNumber();

			void update(sf::Time elapsedTime);
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		private:
			sf::Text text;
			sf::Font font;
	};
}
#endif