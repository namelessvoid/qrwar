#include "gui/guihelper.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

const sf::Texture* GuiHelper::getUnitTexture(UNITTYPES type, Player::Ptr player)
{
	std::string textureName = "p" + std::to_string(player->getId());

	switch(type)
    {
    case EUT_SWORDMAN:
        textureName += "swordman";
        break;
    case EUT_ARCHER:
        textureName += "archer";
        break;
    case EUT_SPEARMAN:
        textureName += "spearman";
        break;
    default:
        textureName = "";
        break;
    }

    TextureManager* textureManager = TextureManager::getInstance();
    const sf::Texture* texture = textureName != "" ? textureManager->getTexture(textureName) : textureManager->getFallbackTexture();
    return texture;
}

std::string GuiHelper::getUnitName(const Unit* unit)
{
    switch(unit->getType())
    {
    case EUT_SWORDMAN:
        return "Swordsman";
    case EUT_ARCHER:
        return "Archer";
    case EUT_SPEARMAN:
        return "Spearman";
    default:
        return "Unknown Unit Type";
    }
}

const sf::Texture *GuiHelper::getTerrainTexture(TERRAINTYPES terrainType)
{
	switch(terrainType)
    {
    case TERRAINTYPES::ET_WOOD:
        return TextureManager::getInstance()->getTexture("wood");
    case TERRAINTYPES::ET_HILL:
        return TextureManager::getInstance()->getTexture("hill");
    default:
        return TextureManager::getInstance()->getFallbackTexture();
    }
}

std::string GuiHelper::getTerrainName(const Terrain* terrain)
{
    switch(terrain->getType())
    {
    case TERRAINTYPES::ET_WOOD:
        return "Wood";
    case TERRAINTYPES::ET_HILL:
        return "Hill";
    default:
        return "Unknown Terrain Type";
    }
}


} // namespace qrw
