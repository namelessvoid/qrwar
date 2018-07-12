#ifndef QRW_TERRAIN_HPP
#define QRW_TERRAIN_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/terraintypes.hpp"
#include "engine/coordinates.hpp"

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
			static Terrain* createTerrain(TERRAINTYPES terrainType);

			static SID typeName;

			Terrain();

			virtual ~Terrain();

			virtual void onDestroy() override;
			virtual void onAddToScene() override;

			int getModificator(MODIFICATORS type);
			const int* getModificators();

			void setType(TERRAINTYPES type) { _type = type; }
			TERRAINTYPES getType() const;

			void setPosition(const Coordinates& position);
			const Coordinates& getPosition() const;

		private:
			void setModificator(MODIFICATORS type, int value);

			void setTexture(const sf::Texture* texture);

			int _modificators[2];
			TERRAINTYPES _type;

			Coordinates _position;

			SpriteComponent* _sprite;
	};
}

#endif
