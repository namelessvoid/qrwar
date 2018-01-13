#include "game/meta/terrainmetaclass.hpp"

#include "engine/terrain.hpp"

namespace qrw
{

TerrainMetaClass::TerrainMetaClass()
{
}

TerrainMetaClass::~TerrainMetaClass()
{
}

void TerrainMetaClass::serialze(GameObject* object, YAML::Emitter& out) const
{
	const Terrain* terrain = dynamic_cast<Terrain*>(object);
	assert(terrain != nullptr);

	out << YAML::BeginMap;
	out << YAML::Key << "type" << YAML::Value << terrain->getType();
	out << YAML::EndMap;
}

std::type_index TerrainMetaClass::getTypeIndex() const
{
	Terrain tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw


