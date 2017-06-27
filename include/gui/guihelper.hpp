#ifndef QRW_GUIHELPER_HPP
#define QRW_GUIHELPER_HPP

#include <string>

#include "engine/unit.hpp"
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
    static const sf::Texture* getUnitTexture(Unit::Ptr unit);

    /**
     * @brief Get the name of a Unit.
     * @param unit Pointer to a Unit.
     * @return String containing the Unit's name.
     */
    static std::string getUnitName(Unit::Ptr unit);

    /**
     * @brief Get texture of a Terrain.
     * @param terrain Pointer to a Terrain.
     * @return Pointer to the Terrain's texture.
     */
    static const sf::Texture* getTerrainTexture(Terrain::Ptr terrain);

    /**
     * @brief Get the name of a Terrain.
     * @param terrain Pointer to a Terrain.
     * @return String containing the Terrain's name.
     */
    static std::string getTerrainName(Terrain::Ptr terrain);


private:
    GuiHelper() {}
};

} // namespace qrw

#endif // QRW_GUIHELPER_HPP
