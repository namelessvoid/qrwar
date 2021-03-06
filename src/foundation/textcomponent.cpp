#include "foundation/textcomponent.hpp"

namespace qrw
{

qrw::TextComponent::TextComponent(GameObject& owner, Layer layer)
	: GameComponent(owner),
	  Renderable(layer)
{
	m_font.loadFromFile("./res/font/Knigqst.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setString("DUMMY_TEXT");
}

void TextComponent::setText(const std::string &text)
{
	m_text.setString(text);
}

void TextComponent::setCharacterSize(int size)
{
	m_text.setCharacterSize(size);
}

void TextComponent::setFillColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

void qrw::TextComponent::render(sf::RenderTarget &renderTarget)
{
	renderTarget.draw(m_text);
}

void qrw::TextComponent::setPosition(const sf::Vector2f &position)
{
	m_text.setPosition(position);
}

const sf::Vector2f &qrw::TextComponent::getPosition() const
{
	return m_text.getPosition();
}

} // namespace qrw
