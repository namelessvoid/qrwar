#ifndef QRW_TEXTUREMANAGER_HPP
#define QRW_TEXTUREMANAGER_HPP

#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>

namespace qrw
{
	/**
	 * @brief Manages loading and supply of textures.
	 *
	 * The TextureManager is a singleton that takes
	 * care of loading and managing sf::Textures.
	 */
	class TextureManager
	{
		public:
			/**
			 * Standard destructor. Deletes all loaded textures!
			 */
			~TextureManager();

			/**
			 * Get the TextureManager instance.
			 */
			static TextureManager* getInstance();

			/**
			 * @brief Loads a texture from disk.
			 *
			 * This Function loads a file from disk and
			 * stores it under it's name in the textures map.
			 * @param texname The name of the texture that is
			 * used to refer to the texture in the textures map.
			 * @param filepath The path to the file containing
			 * the texture.
			 * @return True if the load was successful false if not.
			 */
			bool loadTexture(const std::string texname, const std::string filepath);

			/**
			 * @brief Get pointer to texture.
			 *
			 * This Function searches through the textures map
			 * and returns the texture if it can be found.
			 * @param texname The name of the texture under which
			 * it is stored in the textures map.
			 * @return Pointer to the texture or Null if the
			 * texture cannot be found.
			 */
			const sf::Texture* getTexture(const std::string texname);

		private:
			/**
			 * Singleton constructor.
			 */
			TextureManager();
			
			/**
			 * Singleton self reference.
			 */
			static TextureManager* texturemanager;

			/**
			 * Map that holds all textures.
			 */
			std::map<std::string, sf::Texture*> textures;
	};
}
#endif