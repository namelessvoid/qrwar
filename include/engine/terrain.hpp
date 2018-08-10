#ifndef QRW_TERRAIN_HPP
#define QRW_TERRAIN_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/terraintypes.hpp"
#include "game/skirmish/coordinates.hpp"

#include "foundation/gameobject.hpp"

#include "core/sid.hpp"

namespace qrw
{
	class SpriteComponent;

	enum MODIFICATORS
	{
		EM_ATTACK = 0,
		EM_DEFENSE,
		EM_NUMMODIFICATORS
	};

	class Terrain : public GameObject
	{
		public:
			friend class TerrainMetaClass;

			static Terrain* createTerrain(TERRAINTYPES terrainType);

			static SID typeName;

			Terrain();

			~Terrain() override;

			void onAddToScene() override;

			int getModificator(MODIFICATORS type) const;

			TERRAINTYPES getType() const;

			void setPosition(const Coordinates& position);
			const Coordinates& getPosition() const;

		private:
			int _modificators[2];
			TERRAINTYPES _type;

			Coordinates _position;

			SpriteComponent* _sprite;
	};
}

#endif
