#ifndef QRW_GUIHELPER_HPP
#define QRW_GUIHELPER_HPP

#include <string>

#include "game/skirmish/unit.hpp"
#include "engine/terrain.hpp"

namespace sf
{
class Texture;
}

namespace qrw
{

class GuiHelper
{
public:
	/**
	 * @brief Get texture of a Unit.
	 * @param unit Pointer to a Unit.
	 * @return Pointer to the Unit's texture.
	 */
	static const sf::Texture* getUnitTexture(UNITTYPES type, Player::Ptr player);

	/**
     * @brief Get the name of a Unit.
     * @param unit Pointer to a Unit.
     * @return String containing the Unit's name.
     */
	static std::string getUnitName(const Unit* unit);

    /**
     * @brief Get texture of a Terrain.
     * @param terrain Pointer to a Terrain.
     * @return Pointer to the Terrain's texture.
     */
	static const sf::Texture* getTerrainTexture(TERRAINTYPES terrainType);

    /**
     * @brief Get the name of a Terrain.
     * @param terrain Pointer to a Terrain.
     * @return String containing the Terrain's name.
     */
	static std::string getTerrainName(const Terrain* terrain);


private:
    GuiHelper() {}
};

} // namespace qrw

#endif // QRW_GUIHELPER_HPP
