#ifndef QRW_TILESETPROCESSOR_HPP
#define QRW_TILESETPROCESSOR_HPP value

#include <string>
#include <tinyxml2.h>

#include "gui/texturemanager.hpp"

namespace qrw
{
	class TilesetProcessor
	{
		public:
			TilesetProcessor();
			~TilesetProcessor();

			int loadTileset(std::string filepath);

		private:
			bool processTile(tinyxml2::XMLElement* xmlelement,
				std::string texturefilepath);
			void printAttributeError(int error, std::string attributename);

			TextureManager* texturemanager;
	};
}

#endif