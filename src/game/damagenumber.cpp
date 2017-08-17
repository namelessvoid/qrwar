#include "game/damagenumber.hpp"

#include "foundation/textcomponent.hpp"
#include "foundation/transformanimationcomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

DamageNumber::DamageNumber(int inflictedDamage)
{
	TextComponent* textComponent = new TextComponent(RENDER_LAYER_BILLBOARD);
	addComponent(textComponent);
	textComponent->setText("-" + std::to_string(inflictedDamage));
	textComponent->setPosition({50, 50});
	textComponent->setFillColor(sf::Color::Red);

	TransformAnimationComponent* animation = new TransformAnimationComponent(textComponent);
	addComponent(animation);
}

} // namespace qrw
