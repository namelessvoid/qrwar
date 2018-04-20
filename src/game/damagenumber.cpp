#include "game/damagenumber.hpp"

#include "gui/scene.hpp"

#include "foundation/textcomponent.hpp"
#include "foundation/transformanimationcomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

DamageNumber::DamageNumber()
{
	m_textComponent = new TextComponent(RENDER_LAYER_BILLBOARD);
	addComponent(m_textComponent);
	m_textComponent->setPosition({50, 50});
	m_textComponent->setFillColor(sf::Color::Red);

	m_animation = new TransformAnimationComponent(m_textComponent);
	m_animation->setDuration(1);
	addComponent(m_animation);
}

void DamageNumber::setDamage(int damage)
{
	m_textComponent->setText("-" + std::to_string(damage));
}

void DamageNumber::update(float elapsedTimeInSeconds)
{
	if(!m_animation->isRunning())
		g_scene.destroy(this);
}

void DamageNumber::setPosition(const sf::Vector2f& position)
{
	m_textComponent->setPosition(position);
}

} // namespace qrw
