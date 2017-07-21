#ifndef QRW_TERRAIN_HPP
#define QRW_TERRAIN_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/terraintypes.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	enum MODIFICATORS
	{
		EM_ATTACK,
		EM_DEFENSE
	};

	class Terrain : public sf::RectangleShape
	{
		public:
			typedef std::shared_ptr<Terrain> Ptr;
			static Ptr createTerrain(TERRAINTYPES terrainType);

			~Terrain();

			int getModificator(MODIFICATORS type);
			int* getModificators();
			TERRAINTYPES getType();

			void setPosition(const Coordinates& position);
			const Coordinates& getPosition() const;

		private:
			Terrain(TERRAINTYPES _type, int attackmod, int defensemod, const sf::Texture* texture);

			int _modificators[2];
			TERRAINTYPES _type;

			Coordinates _position;
	};
}

#endif
