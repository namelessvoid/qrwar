#ifndef QRW_TILESETPROCESSOR_HPP
#define QRW_TILESETPROCESSOR_HPP value

#include <string>
#include <tinyxml2.h>

#include "config/xmlhelper.hpp"

namespace qrw
{
class TextureManager;

class TilesetProcessor : public XMLHelper
{
public:
	TilesetProcessor();
	~TilesetProcessor() = default;

	int loadTileset(std::string filepath);

private:
	bool processTile(tinyxml2::XMLElement* xmlelement, std::string texturefilepath);

	TextureManager* texturemanager;
};

} // namespace qrw

#endif
